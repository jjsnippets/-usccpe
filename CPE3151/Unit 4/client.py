import socket
from threading import Thread
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.exceptions import InvalidSignature

# Helper function that waits until all bytes have been recieved
def recv_all(sock, n):
    data = b''
    while len(data) < n:
        packet = sock.recv(n - len(data))
        if not packet:
            return None
        data += packet
    return data

# Thread for receiving messages
def receiveMsg(conn):
    global run

    while run:
        # In normal operation, receive any messages from server
        try:
            # Receive encrypted message length (4 bytes)
            len_bytes = recv_all(conn, 4)
            if not len_bytes: break
            msg_len = int.from_bytes(len_bytes, 'big')

            # Receive encrypted message
            encrypted_data = recv_all(conn, msg_len)
            if not encrypted_data: break

            # Receive signature (256 bytes for 2048-bit RSA)
            signature = recv_all(conn, 256)
            if not signature: break

            # Decrypt message
            decrypted_msg = client_private_key.decrypt(
                encrypted_data,
                padding.OAEP(
                    mgf=padding.MGF1(algorithm=hashes.SHA256()),
                    algorithm=hashes.SHA256(),
                    label=None
                )
            )

            # Verify signature using server's public key
            try:
                server_public_key.verify(
                    signature,
                    decrypted_msg,
                    padding.PSS(
                        mgf=padding.MGF1(hashes.SHA256()),
                        salt_length=padding.PSS.MAX_LENGTH
                    ),
                    hashes.SHA256()
                )
                # If signature matches
                print('\nMessage Received and Verified: {}'.format(decrypted_msg.decode()), flush=True)
                print('Continue Message: ', end='', flush=True)

            # Otherwise, warn user 
            except InvalidSignature:
                print('\nWarning: Message signature verification failed!', flush=True)
                print('Continue Message: ', end='', flush=True)

        # If error, then close connection
        except Exception as e:
            print(f"Error: {e}")
            run = False

    conn.close()

#
# Start of code execution
#
run = True

# Generate client's key pairs
client_private_key = rsa.generate_private_key(       
    public_exponent = 65537,
    key_size = 2048
)

client_public_key = client_private_key.public_key()

# Variable for the other's (server's) public key
server_public_key = None

# Connect to server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 8000))
print('Client connected to server...')

# Exchange public keys
    # Receive server's public key
server_public_pem = s.recv(4096)
server_public_key = serialization.load_pem_public_key(server_public_pem)

    # Send client's public key to server
client_public_pem = client_public_key.public_bytes(
    encoding = serialization.Encoding.PEM,
    format = serialization.PublicFormat.SubjectPublicKeyInfo
)
s.sendall(client_public_pem)

# Start a thread for receiving messages
rcv = Thread(target=receiveMsg, args=(s,), daemon=True)
rcv.start()

# Constant loop for sending messages
while run:
    # In normal operation, send messages to server
    try:
        msg = input("Type Message: ")

        # Sign the message with client's private key
        signature = client_private_key.sign(
            msg.encode(),
            padding.PSS(
                mgf = padding.MGF1(hashes.SHA256()),
                salt_length = padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )

        # Encrypt message with server's public key
        encrypted_msg = server_public_key.encrypt(
            msg.encode(),
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )

        # Send encrypted message length, encrypted message, then signature
        # Basically, concatenating the message
        s.sendall(len(encrypted_msg).to_bytes(4, 'big'))
        s.sendall(encrypted_msg)
        s.sendall(signature)
    
    # If error, then close connection
    except Exception as e:
        print(f"Error: {e}")
        run = False

s.close()
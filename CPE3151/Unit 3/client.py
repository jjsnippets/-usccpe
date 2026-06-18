import socket
from threading import Thread
from cryptography.hazmat.primitives.asymmetric import rsa, padding      # Libraries for RSA-enabled communication
from cryptography.hazmat.primitives import hashes, serialization

# Thread for receiving messages
def receiveMsg(conn):
    global run
    while run:
        # In normal operation, receive any messages from server
        try:
            data = conn.recv(4096)                                  # Larger buffer
            if not data:
                continue
            
            # Decrypt received message with client's private key
            decrypted_msg = client_private_key.decrypt(
                data,
                padding.OAEP(
                    mgf = padding.MGF1(algorithm = hashes.SHA256()),
                    algorithm = hashes.SHA256(),
                    label = None
                )
            )
            print('\nMessage Received: {}'.format(decrypted_msg.decode()))
            print('Continue Message: ')

        # If error, then close connection
        except socket.error as msg:
            run = False
        except KeyboardInterrupt:
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

# Declare variable
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
rcv = Thread(target=receiveMsg, args=(s,))
rcv.start()

# Constant loop for sending messages
while run:
    # In normal operation, send messages to server
    try:
        msg = input("Type Message: ")

        # Encrypt message with server's public key
        encrypted_msg = server_public_key.encrypt(
            msg.encode(),
            padding.OAEP(
                mgf = padding.MGF1(algorithm=hashes.SHA256()),
                algorithm = hashes.SHA256(),
                label = None
            )
        )
        s.sendall(encrypted_msg)
    
    # If error, then close connection
    except socket.error as err:
        run = False
    except KeyboardInterrupt:
        run = False

s.close()
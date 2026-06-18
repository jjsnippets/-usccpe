import socket
from threading import Thread
from cryptography.hazmat.primitives.asymmetric import rsa, padding      # Libraries for RSA-enabled communication
from cryptography.hazmat.primitives import hashes, serialization

# Thread for receiving messages
def receiveMsg(conn):
    global run

    # In normal operation, receive any messages from server
    while run:
        try:
            data = conn.recv(4096)                                  # Larger buffer
            if not data:
                continue
            
            # Decrypt received message with server's private key
            decrypted_msg = server_private_key.decrypt(
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

# Generate server's key pairs
server_private_key = rsa.generate_private_key(
    public_exponent = 65537,
    key_size = 2048
)
server_public_key = server_private_key.public_key()

# declare variable
client_public_key = None

# Listen for client connections
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 8000))
s.listen(1)
conn, addr = s.accept()
print('Server accepted client connection...')

# Exchange of public keys
    # Send server's public key to client
server_public_pem = server_public_key.public_bytes(
    encoding = serialization.Encoding.PEM,
    format = serialization.PublicFormat.SubjectPublicKeyInfo
)
conn.sendall(server_public_pem)

    # Receive client's public key
client_public_pem = conn.recv(4096)
client_public_key = serialization.load_pem_public_key(client_public_pem)

# Start a thread for receiving messages
rcv = Thread(target=receiveMsg, args=(conn, ))
rcv.start()

# Constant loop for sending messages
while run:
    # In normal operation, send messages to client
    try:
        msg = input("Type Message: ")
        
        # Encrypt message with client's public key
        encrypted_msg = client_public_key.encrypt(
            msg.encode(),
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )
        conn.sendall(encrypted_msg)
    
    # If error, then close connection
    except socket.error:
        run = False
    except KeyboardInterrupt:
        run = False

s.close()
import socket
from threading import Thread

run = True

def listenConnection():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('127.0.0.1', 8000))
    s.listen(1)
    conn, addr = s.accept()
    print('Server accepted client connection...')
    return conn, addr, s

def receiveMsg(conn):
    global run
    while run:
        try:
            data = conn.recv(1024)
            if not data:
                continue
            print('\nMessage Received: {}'.format(data.decode()))

        except socket.error as msg:
            run = False
        except KeyboardInterrupt:
            run = False

    conn.close()

if __name__ == '__main__':
    conn, addr, s = listenConnection()
    rcv = Thread(target=receiveMsg, args=(conn, ))
    rcv.start()

    while run:                                          # Moved listening code to main thread
        try:                                            # Copied from client.py
            msg = input("Type Message: ")
            s.sendall(msg.encode())
        except socket.error:
            run = False
        except KeyboardInterrupt:
            run = False
    
    s.close()

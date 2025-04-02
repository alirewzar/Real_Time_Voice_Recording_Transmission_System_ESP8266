import socket
import time

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

clientSocket.connect(("192.168.4.1", 5000))

content1 = bytearray()
i = 0

while True:
    data = input("Enter : ")

    time.sleep(3)

    clientSocket.send(data.encode())
    with open("ali.png", "wb") as f:
        while True:
            temp = clientSocket.recv(4000)
            content1 += temp
            i += 1
            if i == 1000:
                f.write(content1)
                i = 0
                content1 = bytearray()
    print("Closing connection")
client.close()
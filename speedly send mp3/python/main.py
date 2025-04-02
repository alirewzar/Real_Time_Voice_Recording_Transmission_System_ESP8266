import socket

s = socket.socket()
s.bind(('192.168.43.88', 8090))
s.listen(0)
content1 = bytearray()
i = 0

while True:
    client, addr = s.accept()
    with open("ali.png", "wb") as f:
        while True:
            temp = client.recv(4000)
            content1 += temp
            i += 1
            if i == 1000:
                f.write(content1)
                i = 0
                content1 = bytearray()
    print("Closing connection")
client.close()
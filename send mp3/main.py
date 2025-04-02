import socket
import time

s = socket.socket()
s.bind(('192.168.43.88', 8090))
s.listen(0)
d = []
# i = 0
byt = bytearray()
# r = 0
while True:
    client, addr = s.accept()

    with open("ali.pdf", "wb") as f:

        while True:
            # content = client.recv(4).decode()
            # content = int(content)
            # content = content.to_bytes(1, 'little')
            #
            # if len(content) == 0:
            #     continue
            # else:
            #     f.write(content)

            content = client.recv(40000).decode()
            for i in range(0, 10000):
                mm = content[(i*4): (4*i+4)]
                mm = int(mm)
                byt = mm.to_bytes(1, 'little')
                if len(byt) == 0:
                    continue
                else:
                    f.write(byt)
                time.sleep(1 / 1000000)

    print("Closing connection")
    client.close()
import socket

sock = socket.socket()

host = "192.168.43.60"  # ESP32 IP in local network
port = 80  # ESP32 Server Port

sock.connect((host, port))
s = "test"
s = s.encode()
while True:
    sock.send(s)
sock.close()
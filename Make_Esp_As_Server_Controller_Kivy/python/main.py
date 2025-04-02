# ----- A simple TCP client program in Python using send() function -----

import socket

# Create a client socket

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM);

# Connect to the server

clientSocket.connect(("192.168.4.1", 5000));

# Send data to server

data = "Hello Server!";

clientSocket.send(data.encode());

# Receive data from server

dataFromServer = clientSocket.recv(1024);

# Print to the console

print(dataFromServer.decode());

x = 0 ;

while(True):
    x = input("Enter 1 to close and 0 to open : ");
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
    clientSocket.connect(("192.168.4.1", 5000));
    clientSocket.send(x.encode());
    

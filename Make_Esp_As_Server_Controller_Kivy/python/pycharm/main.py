from kivy.app import App
from kivy.properties import StringProperty
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout
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


class WidgetsExample(GridLayout):
    button_change_text = StringProperty("RUN")
    ToggleButton_change_text = StringProperty("RUN")

    def on_button_click(self):
        if(self.x == 1):
            self.x = 0
            self.button_change_text = "on"
        else:
            self.x = 1
            self.button_change_text = "off"

        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
        clientSocket.connect(("192.168.4.1", 5000));
        clientSocket.send(str(self.x).encode());

    def on_togglebutton_click(self, widget):
        if(widget.state == "normal"):
            self.x = 1
            clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
            clientSocket.connect(("192.168.4.1", 5000));
            clientSocket.send(str(self.x).encode());
            self.ToggleButton_change_text = "Off"
        else:
            self.x = 0
            clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
            clientSocket.connect(("192.168.4.1", 5000));
            clientSocket.send(str(self.x).encode());
            self.ToggleButton_change_text = "On"




class MainWidget(Widget):
    pass


class TheLabApp(App):
    pass


TheLabApp().run()

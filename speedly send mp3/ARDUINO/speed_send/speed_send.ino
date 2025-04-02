#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>


const char* ssid = "AlirezaR";
const char* password =  "12345678";
const uint16_t port = 8090;
const char * host = "192.168.43.88";

File myFile;

void setup() {
    Serial.begin(115200); 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("...");
      }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
}
void loop() {
    uint8_t a;
    int i = 0 , j = 0; 
    int t = 2000;
    char buff[t];
    while (!Serial) {;}
    Serial.print("Initializing SD card...");
    
    if (!SD.begin(D8)) {
    Serial.println("initialization failed!");
    while (1);
    }
    
    Serial.println("initialization done.");
    WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
        }
    
    else {
    Serial.println("error opening file");
    }
    
    Serial.println("Connected to server successful!");
    myFile = SD.open("a.png");
  
    while (myFile.available()) {
      for (int i=0; i<t; i++){
      a = myFile.read();
      buff[i]=a;
      j ++;
      }
    client.write(buff,t);
    if(j != t){
      client.write(buff,j);}
      j = 0;
    }
    myFile.close();
    Serial.println("Disconnecting...");
    client.stop();
    delay(1000);
    while(1){delay(2000);}
}

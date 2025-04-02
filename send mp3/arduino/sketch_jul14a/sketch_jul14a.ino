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
    char b[4];
    String kk;
    int i = 0 , j = 0;
    
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
    myFile = SD.open("a.pdf");
  
    while (myFile.available()) {
      a = myFile.read();
      sprintf(b,"%4d",a);
      kk += b;
      i ++;
      j ++;
      if(i == 10000){
        client.print(kk);
        kk = "";
        i = 0;
        j = 0;
        }
    }
    
    if(j != 0){
      client.print(kk);
    }
    
    myFile.close();
     
    Serial.println("Disconnecting...");
    client.stop();
    while(1){delay(2000);}
}

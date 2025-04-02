#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>

WiFiServer server(5000);
WiFiClient client;

File myFile;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPsoftAP_01", "test123456");
  if(result == true)
  {
    Serial.println("Ready");
    server.begin();
    Serial.print("Listening on ");
    Serial.print(WiFi.softAPIP());
    Serial.println("...");
  }
  else
  {
    Serial.println("Failed!");
  }
}

void loop()
{
  uint8_t a;
  int i = 0 , j = 0; 
  int t = 2000;
  char buff[t];
  client = server.available();

  if (!SD.begin(D8)) {
    Serial.println("initialization failed!");
    while (1);
    }
  
  if (client) {
        if(client.connected()){
           Serial.println("Client Connected");
        }
        delay(10000);
        char c = client.read();
        Serial.println(c);
        if (c == 's'){
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
      }
  }
//  else{
//    Serial.println("No Client");
//  }
//delay(1000);
client.stop();
}

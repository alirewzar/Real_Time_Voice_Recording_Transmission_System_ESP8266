#include <ESP8266WiFi.h>

WiFiServer server(5000);
WiFiClient client;


const int output5 = 0;
const int output4 = 2;


void setup()
{
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);


  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);


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
  while(1){
      client = server.available();
        if (client) {
              if(client.connected()){
                Serial.println("Client Connected");
              }
              client.print("Hello from ESP32!");
              while (client.available()>0) {
              char c = client.read();
              Serial.println(c);
              if(c == '1'){
                  digitalWrite(output5, HIGH);
                  digitalWrite(output4, HIGH);
                  Serial.println("1 received");
              }
              else if(c == '0'){
                  digitalWrite(output5, LOW);
                  digitalWrite(output4, LOW);
              }
            }
        }
        else{
          //Serial.println("No Client");
        }
      //delay(3000);
  }
client.stop();
}

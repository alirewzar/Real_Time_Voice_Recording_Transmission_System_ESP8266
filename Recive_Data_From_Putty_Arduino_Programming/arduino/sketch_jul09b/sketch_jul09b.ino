#include <ESP8266WiFi.h>   //library for ESP8266
#include <ESP8266WebServer.h>   //library for server
#include <ArduinoJson.h>   //library for json
#include <DallasTemperature.h>   //libraries for temprature
#include <Wire.h>
#define ONE_WIRE_BUS 0  //pin of sensor

IPAddress local_IP(192,168,11,4);   // Server IP
IPAddress subnet(255,255,255,0);

ESP8266WebServer server;
DynamicJsonDocument doc(1024);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void tempActivity(){
   String Webpage;
   DS18B20.requestTemperatures();
   int temp = DS18B20.getTempCByIndex(0);   // خواندن دما از سنسور
   doc["tempnow"] =temp;
   serializeJson(doc,Webpage);   // ساختار json وارد متغیر webpage می‌شود
   server.send(200, "text/plain",Webpage + "\n" );   // ارسال دیتا به کلاینت‌ها
}

void setup() {
  Serial.begin(115200);
  // تنظیمات وای فای
  WiFi.softAPConfig(local_IP,local_IP,subnet);
  Serial.print("Setting soft_AP ...");
  WiFi.softAP("wemos_d1", "1234567890");
  WiFi.softAPIP();
  WiFi.mode(WIFI_AP);   // تعریف به‌صورت اکسس پوینت

server.begin();
  server.on("/temp", tempActivity);   // وقتی دستور temp برسد تابع tempActivity فراخوانی می‌شود
}

void loop() {
   server.handleClient();   // آماده  بودن برای درخواست کلاینت‌ها
}

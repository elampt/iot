#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define RXD1 16
#define TXD1 17

const char* ssid = "elampt";
const char* password = "elam2002";

unsigned long last_time = 0;
unsigned long timer_delay = 10000;

String json_array;
String robotmessage = "";

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600,SERIAL_8N1, RXD1, TXD1);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("First set of readings will appear after 10 seconds");
  if(WiFi.status()== WL_CONNECTED){
  String server = "http://192.168.195.161:4000/route";
  json_array = GET_Request(server.c_str());
  Serial.println(json_array);
  Serial1.println(json_array);}
}

void loop() {
    robotmessageatus = Serial1.readString(); 
    if(robotmessage!=""){
    if (robotmessage=="Obastacle Detected"){
      Serial.println(robotmessage);  
    } 
    }
    
//  String readfromarduino = Serial1.readString();
//  if readfromarduino!= ""{
//    ESP.reset()
//  }
}


String GET_Request(const char* server) {
  HTTPClient http;    
  http.begin(server);
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}

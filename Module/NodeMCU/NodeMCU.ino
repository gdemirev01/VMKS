#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

//WiFi params
const char* ssid = "Georgi";
const char* password = "0876507601g";

SoftwareSerial s(D2,D3);

//http client for sending requests
HTTPClient http;

//profile params
const char* color;
int turn_on_speed;
int brightness;
int timeout;

String getRequest(String url) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    String payload = "";
    HTTPClient http; 
     
    http.begin(url);
    int httpCode = http.GET();                                                                 
     
    if (httpCode > 0) { 
      payload = http.getString();
    }
    http.end();  
    return payload;
  }  
}

void setup() {
  s.begin(9600);
  
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if(s.available() > 0) {
    char character = s.read();
    if(character == '!') {
      String response = getRequest("http://192.168.1.5:8000/profiles/current_profile/");
      s.print(response);
      s.print('\n');
    }
    character = ' ';
  }
}

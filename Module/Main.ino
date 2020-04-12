#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <timer.h>


#define pir_sensor D7
#define photoresistor D6

#define white_led D4
#define red_led D3

//WiFi params
const char* ssid = "Georgi";
const char* password = "0876507601g";

auto timer = timer_create_default();
bool timerRunning = false;

int steps = 0;

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

void parseJson(String json) {
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(7) + 90;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, json);
  
  JsonObject current_profile = doc["current_profile"];
  
  color = current_profile["color"]; 
  turn_on_speed = (int(current_profile["speed"]) * 50);
  brightness = map(int(current_profile["brightness"]), 1, 10, 100, 1023);
  timeout = int(current_profile["timeout"]) * 1000;

  Serial.println();
  Serial.print(timeout);
  Serial.println();
}

void setup() {

  pinMode(pir_sensor, INPUT);
  pinMode(photoresistor, INPUT);

  pinMode(white_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  digitalWrite(white_led, LOW);
  digitalWrite(red_led, LOW); 

  
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  
  Serial.println();
  Serial.print("Connected ");
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
}

int checkAmbientLight() {
  return !digitalRead(photoresistor);
}

int updateLedColor() {
  int led;
  if(strcmp(color, "red") == 0) {
    led = red_led;
  }
  else if(strcmp(color, "white") == 0) {
    led = white_led;
  }
  else {
    led = -1;
  }
  return led;
}

void detectMovement() {

  if(timerRunning == true) {
    return;
  }
  
  int movement = digitalRead(pir_sensor);
  
  if(movement == 1) {

    Serial.print("movement");
    Serial.println();

    String response = getRequest("http://192.168.1.6:8000/profiles/current_profile/");
    parseJson(response);

    int led = updateLedColor();

    Serial.print(led);
    Serial.println();

    if(led != -1) {    
      Serial.print("turning on");
      Serial.println();
      
      timerRunning = true;
      timer.in(turn_on_speed, turn_led_on, (void*) led);
    }
  }
}

bool turn_led_on(void* argument) {

  if(!timerRunning) {
    steps = 0;
    return false;
  }
  
  steps += (brightness / 80);

  Serial.print(steps);
  Serial.println();

  int led = (int) argument;
  
  analogWrite(led, steps);

  if(steps >= brightness) {
    Serial.print("turning off");
    Serial.println();
    
    steps = 0;
    timer.in(timeout, turn_led_off, (void*) led);
    return false;
  }
  else {
    timer.in(turn_on_speed, turn_led_on, (void*) led);
    return true;
  }
}

bool turn_led_off(void* argument) {

  if(!timerRunning) {
    return false;
  }
  
  int led = (int) argument;
  
  digitalWrite(led, LOW);
  
  timerRunning = false;
  
  return false;
}

void loop() {

  timer.tick();

  int ambientLight = checkAmbientLight();
  
  if(ambientLight) {
    
    digitalWrite(red_led, LOW);
    digitalWrite(white_led, LOW);
    
    timerRunning = false;

    Serial.println();
    Serial.print("ambientLight");
    Serial.println();
  }
  else {
    detectMovement();
  }
}

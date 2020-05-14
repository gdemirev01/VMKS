#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <timer.h>

#define pir_sensor1 7
#define pir_sensor2 8

#define photoresistor 6

#define ledIn 9
#define ledIn2 10

#define green_pin A5
#define red_pin A4
#define blue_pin A3
 
SoftwareSerial s(13,12);

auto timer = timer_create_default();
bool timerRunning = false;

int steps = 0;

//profile params
int red = 0, green = 0, blue = 0;
int turn_on_speed;
int brightness;
int timeout;

boolean newData = false;

String Data = "";

void setup() {
  pinMode(pir_sensor1, INPUT);
  pinMode(photoresistor, INPUT);

  pinMode(green_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  pinMode(ledIn, OUTPUT);
  
  digitalWrite(green_pin, LOW);
  digitalWrite(red_pin, LOW);
  digitalWrite(blue_pin, LOW);
  
  Serial.begin(9600);
  s.begin(9600);
}

bool turn_led_on(void* argument) {

  if(!timerRunning) {
    steps = 0;
    return false;
  }
  
  steps += (brightness / 80);

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

int checkAmbientLight() {
  return !digitalRead(photoresistor);
}

void detectMovement() {

  if(timerRunning == true) {
    return;
  }
  
  int movement = digitalRead(pir_sensor1);
  
  if(movement == 1) {

    s.print('!');

    Serial.print("movement");
    Serial.println();   

    timerRunning = true;
  }
}

void parseJson(String json) {
  
  StaticJsonDocument<500> doc;
  
  deserializeJson(doc, json);
  
  JsonObject current_profile = doc["current_profile"];
  
  red = map(int(current_profile["red"]), 0, 255, 255, 0);
  green = map(int(current_profile["green"]), 0, 255, 255, 0);
  blue = map(int(current_profile["blue"]), 0, 255, 255, 0);
  turn_on_speed = (int(current_profile["speed"]) * 50);
  brightness = map(int(current_profile["brightness"]), 1, 10, 100, 255 );
  timeout = int(current_profile["timeout"]) * 1000;

  analogWrite(green_pin, green);
  analogWrite(red_pin, red);
  analogWrite(blue_pin, blue);
}

void getProfile() {
    char endMarker = '\n';
    char rc;
   
    while (s.available() > 0 && newData == false) {
        rc = s.read();

        if (rc != endMarker) {
            Data.concat(rc);
        }
        else {
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
      
        parseJson(Data);
        
        timer.in(turn_on_speed, turn_led_on, (void*) ledIn);
    
        newData = false;

        Data = "";
    }
}

void loop() {
  timer.tick();

  int ambientLight = !digitalRead(photoresistor);
  
  if(ambientLight) {
   
    digitalWrite(ledIn, LOW);
    
    timerRunning = false;

    Serial.println();
    Serial.print("ambientLight");
    Serial.println();
  }
  else {
    detectMovement();
    getProfile();
    showNewData();
  }
}

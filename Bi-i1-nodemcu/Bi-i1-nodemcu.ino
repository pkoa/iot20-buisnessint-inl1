#include "functions.h"
#include "passwords.h"

#define DEVICE_ID "nodemcu"
#define MSG_LEN 256
#define SENSOR_MIN 0
#define SENSOR_MAX 1024
#define READ_PIN 15

//ssid, pass och connection_string ligger i gitignorad passwords.h fil


int prev_sensor_val = 0;
String formatted_time;

void setup() {
  Serial.begin(115200);
  delay(3000);
  initWifi(ssid, pass);
  initMqtt(connection_string);
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void loop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  int sensor_value = digitalRead(2);
  Serial.println(sensor_value);
  Serial.println(digitalRead(3));
  Serial.println(digitalRead(4));
  Serial.println(digitalRead(5));
  delay(300);
  if(!pending){
    
  }
  
}

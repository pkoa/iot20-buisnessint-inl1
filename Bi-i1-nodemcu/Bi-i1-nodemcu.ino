#include "functions.h"
#include "passwords.h"

#define DEVICE_ID "nodemcu"
#define MSG_LEN 256
#define SENSOR_MIN 0
#define SENSOR_MAX 1024
#define READ_PIN 15

//ssid, pass och connection_string ligger i gitignorad passwords.h fil
//gör en egen sådan eller skriv dessa direkt här och kommentera bort include

int prev_sensor_value = -1, prev_sensor_value_mapped = -1, sensor_value = 0, sensor_value_mapped = 0;
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

  if(!pending){
    sensor_value = hallRead();
    sensor_value_mapped = map(sensor_value, -200, 200, 1, 3);
    formatted_time = timeClient.getFormattedDate();
    if(sensor_value != prev_sensor_value and sensor_value_mapped != prev_sensor_value_mapped){
      pending = true;
      char payload[MSG_LEN];

      DynamicJsonDocument doc(1024);
      doc["deviceid"] = DEVICE_ID;
      doc["halleffect"] = sensor_value;
      doc["formatted_time"] = formatted_time;
      serializeJson(doc, payload);

      EVENT_INSTANCE* message = Esp32MQTTClient_Event_Generate(payload, MESSAGE);
      Esp32MQTTClient_Event_AddProp(message, "name", "Erik");
      Esp32MQTTClient_Event_AddProp(message, "skola", "Nackademin");
      Esp32MQTTClient_SendEventInstance(message);

      prev_sensor_value = sensor_value;
      prev_sensor_value_mapped = sensor_value_mapped;
      
      delay(5000);
    } else {
      delay(5000);
    }
  }
  
}

#include "functions.h"
#include "passwords.h"

#define DEVICE_ID "feather"
#define MSG_LEN 256

//ssid, pass och connection_string ligger i gitignorad passwords.h fil

DHT dht(21, DHT11);
float prev_temp = 0, prev_hum = 0, new_temp, new_hum;
String formatted_time;

void setup() {
  Serial.begin(115200);
  delay(3000);
  initWifi(ssid, pass);
  initMqtt(connection_string);
  dht.begin();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void loop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  
  if(!pending){
    new_temp = dht.readTemperature();
    new_hum = dht.readHumidity();
    formatted_time = timeClient.getFormattedDate();
    if(prev_temp != new_temp or prev_hum != new_hum){
      pending = true;
      char payload[MSG_LEN];
    
      DynamicJsonDocument doc(1024);
      doc["deviceid"] = DEVICE_ID;
      doc["temperature"] = new_temp;
      doc["humidity"] = new_hum;
      doc["formatted_time"] = formatted_time;
      serializeJson(doc, payload);
  
      EVENT_INSTANCE* message = Esp32MQTTClient_Event_Generate(payload, MESSAGE);
      Esp32MQTTClient_SendEventInstance(message);

      prev_temp = new_temp;
      prev_hum = new_hum;
      
      delay(5000);
    } else {
      delay(5000);
    }
    
  }  
}

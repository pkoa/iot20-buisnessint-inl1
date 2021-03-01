#include "functions.h"

#define DEVICE_ID "feather"
#define MSG_LEN 256

char* ssid = "TeliaGateway30-91-8F-E1-3D-A5";
const char* pass = "9FB673595C";
char* connection_string = "HostName=iothub-esp32data.azure-devices.net;DeviceId=iot-esp32;SharedAccessKey=2uocjmN95WovIn62Wom8+GBf8ndlVmqrOWMGgUpnmvA=";
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

#include "AzureIotHub.h"
#include "Esp32MQTTClient.h"
#include <ArduinoJson.h>
#include <DHT.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
bool pending = false;

void initWifi(char* ssid, const char* pass){
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Wifi connected!");
}

void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result){
  if(result == IOTHUB_CLIENT_CONFIRMATION_OK){
    Serial.println("Message confirmed");
    pending = false;
  }
}

void initMqtt(char* connection_string){
  Esp32MQTTClient_Init((uint8_t* )connection_string, true);
  Esp32MQTTClient_SetSendConfirmationCallback(SendConfirmationCallback);
}

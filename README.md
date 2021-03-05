# IOT20 Buissness intelligence inlämningsuppgift 1

Arduinosketcherna använder sig av: https://github.com/taranais/NTPClient/archive/master.zip , för att få fotmatted_time. Finns **INTE** i librarymanager på Arduino IDEn.

## Azurefunctions
### Azurefunction
Sparar och läser från cosmosdb

### SavetoSql
Sparar till azure sqldatabas

## Esp32 baserade MCUer
Båda skickar deviceid, formatted_time med tidsdata. Mitt och skolans namn skickas i json-properties. Notera även att det inte finns några connectionstrings i dessa då de ligger i en gitignore fil, lägg till dina egna

### Bi-i1-feather 
Arduinosketch, använder Dht11. Skickar temperatur och luftfuktighet vid förändring av dessa var 10e sekund.

### Bi-i1-nodemcu
Arduinosketch, använder inbyggd "hall effect" sensor, skickar sensordata vid föränding +-5 eller mer var 10e sekund. 

## Website
En hemsida där datat från cosmosdb visas


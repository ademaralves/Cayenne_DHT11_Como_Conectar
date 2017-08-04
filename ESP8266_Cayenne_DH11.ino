//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN  5

#include "CayenneDefines.h"
#include "BlynkSimpleEsp8266_mod.h"
#include "CayenneWiFiClient.h"
#include <DHT.h>

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "TOKEM";
// Your network name and password.
char ssid[] = "REDE";
char password[] = "SENHA";
//Variables for DHT11 values
float h;
float t;
bool Umidade = false;
bool Temperatura = false;


DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  Serial.print("Setup");
  Cayenne.begin(token, ssid, password);

  Umidade = false;
  Temperatura = false;
  
}

void loop()
{
  //Run Cayenne Functions
  Cayenne.run();

  }


CAYENNE_OUT(V0){
  //Serial.println("Umidade");

  //Check if read failed and try until success
  do {
    //Read humidity (percent)
    h = dht.readHumidity();

    delay(1000);
  } while  (isnan(h));

  Serial.print("Umidade: ");
  Serial.println(h);

  //Set Humidity to true so we know when to sleep
  Umidade = true;

  //Write to Cayenne Dashboard
  Cayenne.virtualWrite(V0, h);
}

CAYENNE_OUT(V1){
  //Serial.println("Temperatura");
  
  //Check if read failed and try until success
  do {
    //Read temperature as Celsius
   
    t = dht.readTemperature();
    

    delay(1000);
  } while  (isnan(t));

  Serial.print("Temperatura: ");
  Serial.println(t);

  //Set Temperature to true so we know when to sleep
  //Temperature = true;

  //Write to Cayenne Dashboard
  Cayenne.virtualWrite(V1, t);
}



##define BLYNK_TEMPLATE_ID "TMPL6valcL2WC"
#define BLYNK_TEMPLATE_NAME "Weather station"
#define BLYNK_AUTH_TOKEN "321BzOSlstdXLLTNjMyAYUG6x30GodJA"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <SimpleTimer.h>

#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;
char auth[] = "321BzOSlstdXLLTNjMyAYUG6x30GodJA";
char ssid[] = "iPhone";
char pass[] = "12345678910";
float t;
float h;

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(2000, sendUptime);
}

void sendUptime()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);
  
}

void loop()
{
  Blynk.run();
  timer.run();
}
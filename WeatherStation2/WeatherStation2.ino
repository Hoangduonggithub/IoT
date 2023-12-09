#define BLYNK_TEMPLATE_ID "TMPL6valcL2WC"
#define BLYNK_TEMPLATE_NAME "Weather station"
#define BLYNK_AUTH_TOKEN "321BzOSlstdXLLTNjMyAYUG6x30GodJA"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <SimpleTimer.h>

#define DHTTYPE DHT11
#define dht_dpin 2
#define sensorPin A0
#define enable2 13
#define RAIN_SENSOR_PIN A0  // Change this to the appropriate pin for your rain sensor
#define RAIN_SENSOR_THRESHOLD 800  // Adjust this threshold based on your rain sensor's characteristics

DHT dht(dht_dpin, DHTTYPE);
SimpleTimer timer;
char auth[] = "321BzOSlstdXLLTNjMyAYUG6x30GodJA";
char ssid[] = "iPhone";
char pass[] = "12345678910";

const char* wifiSsid = "iPhone";
const char* wifiPassword = "12345678910";

WiFiClient client;
int sensorValue2 = 0;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2000, sendUptime);

  pinMode(enable2, OUTPUT);
  WiFi.begin(wifiSsid, wifiPassword);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println("WiFi connected");
}

void sendUptime()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println("Humidity and temperature");
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

  delay(500);
  int sensorValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain sensor value: ");
  Serial.println(sensorValue);
  Blynk.virtualWrite(V4, sensorValue);

  if (sensorValue < RAIN_SENSOR_THRESHOLD)
  {
    Serial.println("Rain is detected");
    Blynk.logEvent("rainalert");
    digitalWrite(enable2, HIGH);
  }
  else
  {
    Serial.println("Rain not detected");
    digitalWrite(enable2, LOW);
  }
  delay(500);
}

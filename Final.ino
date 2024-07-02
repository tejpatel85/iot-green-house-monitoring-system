#include <SFE_BMP180.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h> // Include ThingSpeak library
#include "DHT.h"

DHT dht(D3, DHT11);
SFE_BMP180 bmp;
double T, P;
char status;

const char *ssid = "";       // Your WiFi SSID
const char *pass = "";  // Your WiFi password
const char *server = "api.thingspeak.com";
const int CHANNEL_ID =  // Update with your ThingSpeak Channel ID
const char *apiKey = ""; // Update with your ThingSpeak API Key

WiFiClient client;

const int MQ35_PIN = D0; // Pin connected to MQ35 sensor
const int SOIL_MOISTURE_PIN = D6; // Pin connected to soil moisture sensor

void setup() {
  Serial.begin(9600);
  delay(10);
  bmp.begin();
  Wire.begin();
  dht.begin();
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Initialize ThingSpeak once
  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  // Read temperature and pressure from BMP180 sensor
  status = bmp.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp.getTemperature(T);
    status = bmp.startPressure(3); // 0 to 3
    if (status != 0) {
      delay(status);
      status = bmp.getPressure(P, T);
    }
  }

  // Read humidity and temperature from DHT11 sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Read rain sensor value
  int r = analogRead(A0);
  r = map(r, 0, 1024, 0, 100);
  
  // Read MQ35 sensor value
  int mq35Value = digitalRead(MQ35_PIN);

  // Read soil moisture sensor value
  int soilMoistureValue = digitalRead(SOIL_MOISTURE_PIN);

  // Print values to serial
  Serial.print("Temperature in °C: ");
  Serial.println(t);
  Serial.print("Humidity in %: ");
  Serial.println(h);
  Serial.print("Absolute pressure in mb: ");
  Serial.println(P);
  Serial.print("Rain: ");
  Serial.println(r);
  Serial.print("MQ35 in ppm: ");
  Serial.println(mq35Value);
  Serial.print("Soil Moisture in cb: ");
  Serial.println(soilMoistureValue);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, r);
  ThingSpeak.setField(4, mq35Value);
  ThingSpeak.setField(5, soilMoistureValue);

  int status = ThingSpeak.writeFields(CHANNEL_ID, apiKey);

  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully!");
  } else {
    Serial.println("Failed to send data to ThingSpeak. Status code: " + String(status));
  }

  delay(20000); // Update interval (in milliseconds) - adjust as needed
}

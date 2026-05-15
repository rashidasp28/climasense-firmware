#include <Arduino.h>
#include <DHT.h>
#include "sensors.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void initializeSensors() {
  Serial.println("Initializing ClimaSense sensor layer...");
  dht.begin();
}

ClimateReading readClimateSensors() {
  ClimateReading reading;

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  bool healthy = !(isnan(humidity) || isnan(temperature));

  if (!healthy) {
    Serial.println("Failed to read from DHT sensor");

    humidity = -1;
    temperature = -1;
  }

  reading.temperatureC = temperature;
  reading.humidityPercent = humidity;
  reading.heatIndexC = dht.computeHeatIndex(temperature, humidity, false);

  // Placeholder values until physical sensors are integrated.
  reading.pm25 = 18.0;
  reading.pm10 = 40.0;
  reading.soilMoisturePercent = 35.0;
  reading.rainfallMm = 0.0;
  reading.batteryVoltage = 4.05;
  reading.dhtHealthy = healthy;

  return reading;
}

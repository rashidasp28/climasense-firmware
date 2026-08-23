#include <Arduino.h>
#include <DHT.h>
#include "config_loader.h"
#include "sensors.h"

DHT dht(DHT_PIN, DHT_TYPE);

float readBatteryVoltage() {
  int adcValue = analogRead(BATTERY_ADC_PIN);

  float voltage = (
    (adcValue * ADC_REFERENCE_VOLTAGE) / ADC_RESOLUTION
  ) * BATTERY_DIVIDER_RATIO;

  return voltage;
}

float readSoilMoisturePlaceholder() {
  int adcValue = analogRead(SOIL_MOISTURE_ADC_PIN);

  float percentage = map(adcValue, 0, 4095, 100, 0);

  return percentage;
}

void initializeSensors() {
  Serial.println("Initializing ClimaSense sensor layer...");

  dht.begin();

  pinMode(BATTERY_ADC_PIN, INPUT);
  pinMode(SOIL_MOISTURE_ADC_PIN, INPUT);
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

  // Placeholder values until PM and rainfall sensors are integrated.
  reading.pm25 = 18.0;
  reading.pm10 = 40.0;
  reading.rainfallMm = 0.0;

  reading.soilMoisturePercent = readSoilMoisturePlaceholder();
  reading.batteryVoltage = readBatteryVoltage();
  reading.dhtHealthy = healthy;

  return reading;
}

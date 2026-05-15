#pragma once

struct ClimateReading {
  float temperatureC;
  float humidityPercent;
  float heatIndexC;
  float pm25;
  float pm10;
  float soilMoisturePercent;
  float rainfallMm;
  float batteryVoltage;
  bool dhtHealthy;
};

void initializeSensors();
ClimateReading readClimateSensors();

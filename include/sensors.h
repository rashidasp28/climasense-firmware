#pragma once

struct ClimateReading {
  float temperatureC;
  float humidityPercent;
  float pm25;
  float pm10;
  float soilMoisturePercent;
  float rainfallMm;
  float batteryVoltage;
};

void initializeSensors();
ClimateReading readClimateSensors();

#include <Arduino.h>
#include "sensors.h"

// MVP placeholder sensor layer.
// Replace simulated values with real sensor drivers.

void initializeSensors() {
  Serial.println("Initializing ClimaSense sensor layer...");
}

ClimateReading readClimateSensors() {
  ClimateReading reading;

  reading.temperatureC = 34.5;
  reading.humidityPercent = 62.0;
  reading.pm25 = 18.0;
  reading.pm10 = 40.0;
  reading.soilMoisturePercent = 35.0;
  reading.rainfallMm = 0.0;
  reading.batteryVoltage = 4.05;

  return reading;
}

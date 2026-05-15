#pragma once

// Copy this file to config.h for real deployments.
// Do not commit secrets.

#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define MQTT_HOST "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "climasense/ghana/northern/readings"

#define DEVICE_ID "CS-GH-NR-0001"
#define SCHOOL_ID "PILOT-SCHOOL-001"
#define COMMUNITY_NAME "Tamale"

// Sensor pins
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define BATTERY_ADC_PIN 34
#define SOIL_MOISTURE_ADC_PIN 35
#define RAIN_GAUGE_PIN 27

// Battery voltage divider calibration
// Example: R1 = 100k, R2 = 100k gives divider ratio 2.0
#define ADC_REFERENCE_VOLTAGE 3.3
#define ADC_RESOLUTION 4095.0
#define BATTERY_DIVIDER_RATIO 2.0

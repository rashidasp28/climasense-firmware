#pragma once

// Copy this file to climasense_config.h for real deployments.
// Do not commit secrets.

#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define MQTT_HOST "mqtt.example.com"
#define MQTT_PORT 8883
#define MQTT_TOPIC "climasense/example/readings"
#define MQTT_USERNAME "YOUR_DEVICE_USERNAME"
#define MQTT_PASSWORD "YOUR_DEVICE_PASSWORD"

// Replace this example with the root CA certificate for your MQTT broker.
// Root CA certificates are public trust anchors, not private device credentials.
#define MQTT_ROOT_CA R"EOF(
-----BEGIN CERTIFICATE-----
REPLACE_WITH_BROKER_ROOT_CA_CERTIFICATE
-----END CERTIFICATE-----
)EOF"

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

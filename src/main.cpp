#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.example.h"
#include "sensors.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

unsigned long lastPublish = 0;
const unsigned long publishIntervalMs = 60000;

void connectToWifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
}

void connectToMqtt() {
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");

    if (mqttClient.connect(DEVICE_ID)) {
      Serial.println("connected");
    } else {
      Serial.println("failed, retrying...");
      delay(5000);
    }
  }
}

void publishReading(const ClimateReading& reading) {
  char payload[512];

  snprintf(
    payload,
    sizeof(payload),
    "{\"device_id\":\"%s\",\"temperature_c\":%.2f,\"humidity_percent\":%.2f,\"pm25_ugm3\":%.2f}",
    DEVICE_ID,
    reading.temperatureC,
    reading.humidityPercent,
    reading.pm25
  );

  Serial.println(payload);
  mqttClient.publish(MQTT_TOPIC, payload);
}

void setup() {
  Serial.begin(115200);

  initializeSensors();
  connectToWifi();
  connectToMqtt();
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }

  mqttClient.loop();

  unsigned long now = millis();

  if (now - lastPublish >= publishIntervalMs || lastPublish == 0) {
    ClimateReading reading = readClimateSensors();
    publishReading(reading);
    lastPublish = now;
  }
}

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
  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());
}

void connectToMqtt() {
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");

    if (mqttClient.connect(DEVICE_ID)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

void publishReading(const ClimateReading& reading) {
  char payload[768];

  snprintf(
    payload,
    sizeof(payload),
    "{"
    "\"device_id\":\"%s\"," 
    "\"school_id\":\"%s\"," 
    "\"community\":\"%s\"," 
    "\"temperature_c\":%.2f," 
    "\"humidity_percent\":%.2f," 
    "\"heat_index_c\":%.2f," 
    "\"pm25_ugm3\":%.2f," 
    "\"pm10_ugm3\":%.2f," 
    "\"soil_moisture_percent\":%.2f," 
    "\"rainfall_mm\":%.2f," 
    "\"battery_voltage\":%.2f," 
    "\"wifi_rssi\":%d," 
    "\"dht_healthy\":%s"
    "}",
    DEVICE_ID,
    SCHOOL_ID,
    COMMUNITY_NAME,
    reading.temperatureC,
    reading.humidityPercent,
    reading.heatIndexC,
    reading.pm25,
    reading.pm10,
    reading.soilMoisturePercent,
    reading.rainfallMm,
    reading.batteryVoltage,
    WiFi.RSSI(),
    reading.dhtHealthy ? "true" : "false"
  );

  Serial.println("Publishing climate-health payload:");
  Serial.println(payload);

  mqttClient.publish(MQTT_TOPIC, payload);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ClimaSense Firmware Starting...");

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

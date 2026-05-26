#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#ifdef __has_include
  #if __has_include("config.h")
    #include "config.h"
  #else
    #include "config.example.h"
  #endif
#else
  #include "config.example.h"
#endif

#include "sensors.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

unsigned long lastPublish = 0;
unsigned long lastWifiRetry = 0;
const unsigned long publishIntervalMs = 60000;
const unsigned long wifiTimeoutMs = 15000;
const unsigned long mqttRetryDelayMs = 5000;

bool connectToWifi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < wifiTimeoutMs) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected. IP: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  Serial.println("WiFi connection failed. Device will continue running and retry later.");
  return false;
}

bool connectToMqtt() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  if (mqttClient.connected()) {
    return true;
  }

  Serial.print("Connecting to MQTT...");

  if (mqttClient.connect(DEVICE_ID)) {
    Serial.println("connected");
    return true;
  }

  Serial.print("failed, rc=");
  Serial.println(mqttClient.state());
  return false;
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
    WiFi.status() == WL_CONNECTED ? WiFi.RSSI() : 0,
    reading.dhtHealthy ? "true" : "false"
  );

  Serial.println("Climate-health payload:");
  Serial.println(payload);

  if (connectToMqtt()) {
    bool published = mqttClient.publish(MQTT_TOPIC, payload);
    Serial.println(published ? "MQTT publish successful" : "MQTT publish failed");
  } else {
    Serial.println("MQTT unavailable. Reading was not published.");
  }
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
  if (WiFi.status() != WL_CONNECTED && millis() - lastWifiRetry > mqttRetryDelayMs) {
    connectToWifi();
    lastWifiRetry = millis();
  }

  if (mqttClient.connected()) {
    mqttClient.loop();
  }

  unsigned long now = millis();

  if (now - lastPublish >= publishIntervalMs || lastPublish == 0) {
    ClimateReading reading = readClimateSensors();
    publishReading(reading);
    lastPublish = now;
  }
}

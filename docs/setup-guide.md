# ClimaSense Firmware Setup Guide

## Requirements

- ESP32 development board
- DHT22 sensor
- USB cable
- Arduino IDE or PlatformIO
- WiFi connection

## Wiring

### DHT22

| DHT22 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |

## Installation

1. Clone the repository.
2. Open the project in PlatformIO.
3. Copy `include/config.example.h` to `include/config.h`.
4. Update WiFi and MQTT settings.
5. Build and upload firmware.

## Serial Monitor

Expected startup logs:

```text
ClimaSense Firmware Starting...
Initializing ClimaSense sensor layer...
Connecting to WiFi...
Connecting to MQTT...
```

## Current MVP Sensors

- DHT22 temperature and humidity
- Simulated PM2.5/PM10 values
- ADC-based soil moisture placeholder
- Battery voltage monitoring

## Planned Additions

- PMS5003 air quality sensor
- Rainfall gauge
- Deep sleep optimization
- Offline buffering
- OTA firmware updates

# ClimaSense Firmware Setup Guide

## Requirements

- ESP32 development board
- DHT22 sensor
- USB data cable and the appropriate USB-to-serial driver
- Visual Studio Code with the PlatformIO IDE extension, or PlatformIO Core 6.1.19
- Internet access for PlatformIO's initial dependency download

The reproducible build uses the `esp32dev` environment declared in
`platformio.ini`, including Espressif 32 platform 7.0.1. An active Wi-Fi or
MQTT connection is not required to compile the firmware.

## Wiring

### DHT22

| DHT22 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |

## Installation

1. Clone the repository.
2. Open the repository root in PlatformIO.
3. Copy `include/config.example.h` to the untracked local file
   `include/climasense_config.h`.
4. Replace the Wi-Fi and MQTT placeholders only in
   `include/climasense_config.h`.
5. Build the firmware with `pio run` before connecting a device.
6. With the ESP32 connected, upload with `pio run --target upload`.

On macOS or Linux:

```bash
cp include/config.example.h include/climasense_config.h
pio run
```

On Windows PowerShell:

```powershell
Copy-Item include/config.example.h include/climasense_config.h
pio run
```

`include/climasense_config.h` is excluded by `.gitignore`. Never commit or
paste its Wi-Fi password, MQTT credentials, or broker configuration into an
issue or build log. The checked-in example configuration is compile-safe but
cannot connect to a real broker until its placeholders are replaced.

## Serial Monitor

Start the monitor after uploading:

```bash
pio device monitor --baud 115200
```

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

For clean builds, verbose compiler diagnostics, and safe failure reporting,
see the [local firmware development guide](local-development.md).

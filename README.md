# ClimaSense Firmware

Open-source ESP32 firmware for the ClimaSense climate-health monitoring node.

ClimaSense is an ISIR Ghana initiative for climate-resilient child health and education in Northern Ghana. The firmware collects hyperlocal environmental data from low-cost sensors and publishes readings to an MQTT broker for dashboards, alerts, and school-based learning activities.

## Core Features

- ESP32-based environmental monitoring
- Temperature and humidity sensing
- Particulate matter sensor support placeholder
- Rainfall and soil moisture support placeholder
- Authenticated MQTT data publishing over certificate-validated TLS
- Offline-safe serial logging
- School-friendly code structure for learning and adaptation

## Target Hardware

Minimum prototype node:

- ESP32 development board
- DHT22 or SHT31 temperature and humidity sensor
- PMS5003 or SDS011 particulate matter sensor
- Soil moisture sensor
- Rain gauge tipping bucket module
- Solar charging system and battery pack

## Data Flow

Sensor Node -> MQTT Broker -> API/Data Pipeline -> Dashboard -> Alerts

See the [telemetry payload contract](docs/telemetry-payload.md) for field names, units, data-quality indicators, placeholder values, and compatibility rules.

## Development

See the [local firmware development guide](docs/local-development.md) for PlatformIO setup, configuration, building, uploading, serial monitoring, and safe compiler-error reporting.

Quick build:

```bash
pio run
```

## Repository Status

Initial MVP scaffold. Built for rapid UNICEF Venture Fund prototype development.

## License

MIT License for firmware and software.

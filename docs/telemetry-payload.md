# Telemetry payload contract

This document describes the JSON message published by the ClimaSense firmware. It is intended to keep the firmware, ingestion API, dashboard, and alert engine aligned while the prototype evolves.

## Transport

- Protocol: MQTT over certificate-validated TLS
- Topic: configured by `MQTT_TOPIC`
- Publish interval: 60 seconds
- Encoding: UTF-8 JSON
- Delivery behavior: the current prototype publishes without MQTT retained-message or quality-of-service configuration
- Offline behavior: failed publishes are logged to the serial console but are not buffered for later delivery

## Payload

```json
{
  "device_id": "climasense-node-001",
  "school_id": "school-001",
  "community": "example-community",
  "temperature_c": 31.42,
  "humidity_percent": 68.10,
  "heat_index_c": 36.27,
  "pm25_ugm3": 18.00,
  "pm10_ugm3": 40.00,
  "soil_moisture_percent": 54.00,
  "rainfall_mm": 0.00,
  "battery_voltage": 4.08,
  "wifi_rssi": -61,
  "dht_healthy": true
}
```

The identifiers above are illustrative and must not be treated as deployment credentials or approved production values.

## Field definitions

| Field | JSON type | Unit | Source and meaning |
| --- | --- | --- | --- |
| `device_id` | string | none | Deployment identifier configured as `DEVICE_ID`. It should be unique per physical node. |
| `school_id` | string | none | School or installation identifier configured as `SCHOOL_ID`. |
| `community` | string | none | Human-readable deployment area configured as `COMMUNITY_NAME`. Avoid precise household locations or personal data. |
| `temperature_c` | number | degrees Celsius | DHT temperature reading. The current firmware emits `-1` when the DHT read fails. |
| `humidity_percent` | number | percent relative humidity | DHT humidity reading. The current firmware emits `-1` when the DHT read fails. |
| `heat_index_c` | number | degrees Celsius | Heat index calculated from the temperature and humidity readings. Consumers must check `dht_healthy` before using it. |
| `pm25_ugm3` | number | micrograms per cubic metre | PM2.5 concentration. Currently a fixed prototype placeholder until a particulate sensor is integrated. |
| `pm10_ugm3` | number | micrograms per cubic metre | PM10 concentration. Currently a fixed prototype placeholder until a particulate sensor is integrated. |
| `soil_moisture_percent` | number | percent | Raw ADC value mapped to a percentage. This is an uncalibrated prototype reading. |
| `rainfall_mm` | number | millimetres | Rainfall total. Currently a fixed prototype placeholder until a rain gauge is integrated. |
| `battery_voltage` | number | volts | ADC-derived battery voltage using the configured reference and divider ratio. |
| `wifi_rssi` | integer | dBm | Wi-Fi received signal strength. The firmware emits `0` when Wi-Fi is disconnected. |
| `dht_healthy` | boolean | none | `true` only when both DHT temperature and humidity reads succeeded. |

## Consumer rules

1. Validate the JSON structure and field types before storing a reading.
2. Use `device_id` together with deployment records to identify the node. Do not trust a device identifier as proof of authenticity by itself.
3. Reject or quarantine impossible values according to an approved validation policy.
4. Treat PM2.5, PM10, rainfall, and soil moisture as non-production data until their real sensors and calibration procedures are implemented.
5. Ignore temperature, humidity, and heat index for health decisions when `dht_healthy` is `false`.
6. Store the ingestion timestamp on the server. The current firmware payload does not include a device timestamp.
7. Keep alert thresholds outside the firmware so rule changes remain versioned and reviewable.

## Compatibility policy

The field names in this document form the prototype payload contract. Additive fields may be introduced without breaking existing consumers. Renaming, removing, or changing the meaning or unit of an existing field requires coordinated updates across the firmware, API, dashboard, alert engine, and their tests.

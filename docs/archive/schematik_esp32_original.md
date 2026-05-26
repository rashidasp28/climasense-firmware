# Original Schematik ESP32 Firmware Reference

This file archives the original Schematik-generated ClimaSense firmware draft for traceability.

The original `.ino` source has intentionally been moved out of the PlatformIO example tree to avoid accidental compilation during CI builds.

## Status

- Original reviewed: 2026-05-25
- Current refined firmware location:
  - `src/main.cpp`
  - `src/sensors.cpp`
  - `include/sensors.h`
  - `include/config.example.h`

## Reason for Archiving

The Schematik-generated firmware was useful as an early reference, but the production-oriented ClimaSense firmware now follows the repository architecture and aligns with:

- refined hardware BOM,
- refined assembly guide,
- professional wiring architecture,
- Wi-Fi-first deployment strategy,
- MQTT telemetry,
- and ClimaSense API schema.

The original `.ino` should not be treated as the active firmware.

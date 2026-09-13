# MQTT data schema

This filename is retained for compatibility with older links. The authoritative schema is the [telemetry payload contract](telemetry-payload.md).

Do not implement an ingestion service from the abbreviated example that previously appeared on this page. It omitted required identity, data-quality, environmental, battery, and connectivity fields.

## Current integration rules

- Read the MQTT topic from the deployment's `MQTT_TOPIC` configuration. The firmware does not require one hard-coded topic.
- Validate the complete field set, JSON types, units, placeholder status, and compatibility policy documented in the telemetry payload contract.
- Treat additive fields as backward compatible.
- Coordinate any renamed, removed, or redefined field across the firmware, ingestion API, dashboard, alert engine, and tests.
- Store the server ingestion time because the current device payload does not contain a device timestamp.

Update the canonical contract first whenever the firmware payload changes. This compatibility page should remain a pointer rather than a second, independently maintained schema.

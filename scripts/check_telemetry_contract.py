#!/usr/bin/env python3
"""Verify that firmware and documentation expose the same telemetry fields."""

from __future__ import annotations

import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
FIRMWARE_PATH = ROOT / "src" / "main.cpp"
CONTRACT_PATH = ROOT / "docs" / "telemetry-payload.md"

REQUIRED_FIELDS = {
    "device_id",
    "school_id",
    "community",
    "temperature_c",
    "humidity_percent",
    "heat_index_c",
    "pm25_ugm3",
    "pm10_ugm3",
    "soil_moisture_percent",
    "rainfall_mm",
    "battery_voltage",
    "wifi_rssi",
    "dht_healthy",
}


def firmware_fields(source: str) -> list[str]:
    """Extract JSON keys from the escaped C++ payload format string."""
    return re.findall(r'\\\"([a-z][a-z0-9_]*)\\\"\s*:', source)


def documented_fields(markdown: str) -> list[str]:
    """Extract keys from the field-definition table."""
    return re.findall(r"^\| `([a-z][a-z0-9_]*)` \|", markdown, re.MULTILINE)


def example_fields(markdown: str) -> list[str]:
    """Extract keys from the first fenced JSON payload example."""
    match = re.search(r"```json\s*(\{.*?\})\s*```", markdown, re.DOTALL)
    if not match:
        raise ValueError("telemetry contract has no fenced JSON example")
    payload = json.loads(match.group(1))
    if not isinstance(payload, dict):
        raise ValueError("telemetry example must be a JSON object")
    return list(payload)


def duplicate_fields(fields: list[str]) -> set[str]:
    return {field for field in fields if fields.count(field) > 1}


def validate_contract(source: str, markdown: str) -> list[str]:
    firmware = firmware_fields(source)
    documented = documented_fields(markdown)
    example = example_fields(markdown)
    errors: list[str] = []

    for label, fields in (
        ("firmware payload", firmware),
        ("field-definition table", documented),
        ("JSON example", example),
    ):
        duplicates = duplicate_fields(fields)
        if duplicates:
            errors.append(f"{label} contains duplicate fields: {sorted(duplicates)}")

    firmware_set = set(firmware)
    documented_set = set(documented)
    example_set = set(example)

    if firmware_set != documented_set:
        errors.append(
            "firmware/table mismatch: "
            f"firmware-only={sorted(firmware_set - documented_set)}, "
            f"table-only={sorted(documented_set - firmware_set)}"
        )
    if firmware_set != example_set:
        errors.append(
            "firmware/example mismatch: "
            f"firmware-only={sorted(firmware_set - example_set)}, "
            f"example-only={sorted(example_set - firmware_set)}"
        )

    missing_required = REQUIRED_FIELDS - firmware_set
    if missing_required:
        errors.append(f"required fields are missing: {sorted(missing_required)}")

    return errors


def main() -> int:
    errors = validate_contract(
        FIRMWARE_PATH.read_text(encoding="utf-8"),
        CONTRACT_PATH.read_text(encoding="utf-8"),
    )
    if errors:
        for error in errors:
            print(f"ERROR: {error}")
        return 1

    print(f"Telemetry contract check passed for {len(REQUIRED_FIELDS)} fields.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

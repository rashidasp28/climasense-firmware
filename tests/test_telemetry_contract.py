import importlib.util
import sys
import unittest
from pathlib import Path


MODULE_PATH = Path(__file__).parents[1] / "scripts" / "check_telemetry_contract.py"
SPEC = importlib.util.spec_from_file_location("check_telemetry_contract", MODULE_PATH)
assert SPEC and SPEC.loader
contract = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = contract
SPEC.loader.exec_module(contract)


def firmware_for(fields: list[str]) -> str:
    return "\n".join(f'    "\\\"{field}\\\":0,"' for field in fields)


def markdown_for(fields: list[str]) -> str:
    example = {field: 0 for field in fields}
    table = "\n".join(f"| `{field}` | number | none | test |" for field in fields)
    import json

    return f"```json\n{json.dumps(example)}\n```\n\n{table}\n"


class TelemetryContractTests(unittest.TestCase):
    def test_matching_contract_passes(self):
        fields = sorted(contract.REQUIRED_FIELDS)
        self.assertEqual(contract.validate_contract(firmware_for(fields), markdown_for(fields)), [])

    def test_firmware_documentation_drift_fails(self):
        fields = sorted(contract.REQUIRED_FIELDS)
        markdown = markdown_for(fields).replace("`wifi_rssi`", "`signal_strength`")
        errors = contract.validate_contract(firmware_for(fields), markdown)
        self.assertTrue(any("firmware/table mismatch" in error for error in errors))

    def test_missing_required_field_fails(self):
        fields = sorted(contract.REQUIRED_FIELDS - {"device_id"})
        errors = contract.validate_contract(firmware_for(fields), markdown_for(fields))
        self.assertIn("required fields are missing: ['device_id']", errors)

    def test_duplicate_field_fails(self):
        fields = sorted(contract.REQUIRED_FIELDS)
        firmware = firmware_for(fields + ["device_id"])
        errors = contract.validate_contract(firmware, markdown_for(fields))
        self.assertTrue(any("duplicate fields" in error for error in errors))


if __name__ == "__main__":
    unittest.main()

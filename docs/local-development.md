# Local firmware development

This guide provides a reproducible way to build the ClimaSense ESP32 firmware and capture the first actionable compiler error.

## Prerequisites

Install:

- Git
- Visual Studio Code with the PlatformIO IDE extension, or PlatformIO Core
- A USB data cable and the appropriate ESP32 USB-to-serial driver for device upload

## Clone and open the project

```bash
git clone https://github.com/rashidasp28/climasense-firmware.git
cd climasense-firmware
```

Open the repository folder in Visual Studio Code. PlatformIO should detect `platformio.ini` and install the declared ESP32 platform and libraries.

## Configure local credentials

Copy the example configuration and edit only the untracked copy:

```bash
cp include/config.example.h include/config.h
```

On Windows PowerShell:

```powershell
Copy-Item include/config.example.h include/config.h
```

Set local Wi-Fi and MQTT values in `include/config.h`. Never commit this file. It is excluded by `.gitignore`.

## Build from PlatformIO

In Visual Studio Code:

1. Open the PlatformIO sidebar.
2. Select **Project Tasks > esp32dev > General > Build**.
3. Wait for dependency installation and compilation to finish.

From a terminal with PlatformIO Core installed:

```bash
pio run
```

A successful build ends with `SUCCESS`.

## Capture a useful failure report

If the build fails:

1. Run a clean build:

   ```bash
   pio run --target clean
   pio run --verbose
   ```

2. Record the operating system, PlatformIO Core version, Python version, and the complete first compiler error block.
3. Include the lines immediately before and after the first `error:` message.
4. Do not share Wi-Fi passwords, MQTT credentials, tokens, or the contents of `include/config.h`.
5. Attach the sanitized output to the relevant GitHub issue.

Useful version commands:

```bash
pio --version
python --version
git --version
```

## Upload and monitor

After a successful build and with the ESP32 connected:

```bash
pio run --target upload
pio device monitor --baud 115200
```

Confirm that the serial output reports sensor initialization and connection status. Use placeholder or test credentials for development hardware.

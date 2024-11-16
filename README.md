# FritzGate
**FritzGate** transforms your **Ai Thinker board** into a smart thermostat controller. This project enables seamless control of thermostats connected to a **FRITZ!Box**, integrating any of 70+ temperature sensors models for precise temperature control.

![FritzGate screenshot](docs/FritzGate_Screenshot.svg)

## Demo

You can view a demo of the FritzGate interface [here](https://vnau.github.io/FritzGate/).

## Features

- **FRITZ!Box integration:** FritzGate does not affect weekly plans or other thermostat settings. Connect and control thermostats directly from FritzBox.
- **Binding with external Temperature Sensors:** Utilize third party temperature sensors placed in living spaces for precise temperature control in a room. FritzGate automatically corrects temperature offsets of thermostat sensors.
- **Embedded Web Server:** Easily manage thermostat-sensor bindings, monitor temperature and humidity through a user-friendly web interface.

## Advantages

- **Easy Configuration:** Set up effortlessly by scanning a QR code with the Ai Thinker camera for Wi-Fi credentials.
- **Cost-Effective Hardware:** Utilize the budget-friendly and energy efficient **ESP32-CAM** board.
- **Powered by FRITZ!Box:** Leverage the convenience of powering the device directly from the *FRITZ!Box** USB port, eliminating the need for additional space and power sources.
- **70+ Supported Sensors:** Use any of [70+ models](https://decoder.theengs.io/devices/devices.html) of temperature sensors for precise climate control in living spaces, ensuring optimal comfort and energy savings.
- **Embedded Web Server:** Easily manage thermostat-sensor bindings through the embedded web server, providing an intuitive interface for users to customize and monitor their smart heating system.
- **Can be used without FRITZ!Box:** If you're not authorized in FritzBox, you can still monitor temperature and humidity from nearby temperature sensors.

## Getting Started

### Hardware Requirements

- Ai Thinker ESP32-CAM board
- [Temperature sensors](https://decoder.theengs.io/devices/devices.html)
- Fritzbox with compatible thermostats (optional)

### Installation

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/vnau/FritzGate.git
    ```

2. Open the project in [PlatformIO](https://platformio.org/) or [Arduino IDE](https://www.arduino.cc/en/software), depending on your preference.

3. **For PlatformIO Users:**
   - Upload the code to your Ai Thinker ESP32-CAM board.
   - After the first start, use the Ai Thinker ESP32-CAM board camera to scan the Wi-Fi QR code. This will configure the Wi-Fi credentials automatically.

4. **For Arduino IDE Users:**
   - Ensure you have  [NTPClient](https://github.com/arduino-libraries/NTPClient) and [ArduinoJson](https://github.com/bblanchon/ArduinoJson) Arduino libraries installed before building the project.
   - Set Wi-Fi credentials directly in the code (alternatively, you can install the [ESP32QRCodeReader](https://github.com/alvarowolfx/ESP32QRCodeReader) library from Github to be able to read the WiFi QR code).
   - Upload the code to your Ai Thinker ESP32-CAM board.

5. Access the web interface by navigating to the assigned IP address in your web browser.

# IoT Weather Station

This project is an IoT Weather Station built using an ESP8266 microcontroller (NodeMCU), various sensors, and ThingSpeak platform for data visualization.

## Description

The IoT Weather Station collects environmental data including temperature, humidity, pressure, rain, air quality, and soil moisture. It then sends this data to ThingSpeak, an IoT platform, for storage and visualization.

## Components

- ESP8266 (NodeMCU) microcontroller
- BMP180 sensor for temperature and pressure
- DHT11 sensor for humidity and temperature
- Rain sensor
- MQ35 gas sensor
- Soil moisture sensor

## Prerequisites

- Arduino IDE
- ESP8266 board package installed in Arduino IDE
- Libraries:
  - SFE_BMP180
  - DHT sensor library
  - ThingSpeak library

## Setup

1. Connect the sensors to the ESP8266 microcontroller.
2. Install the necessary libraries in your Arduino IDE.
3. Configure your WiFi credentials, ThingSpeak Channel ID, and API Key in the code.
4. Upload the code to your ESP8266 board.
5. Monitor the data on the ThingSpeak dashboard.

## Usage

- The ESP8266 reads sensor data periodically.
- Data is sent to ThingSpeak for visualization and analysis.
- Adjust the update interval in the code according to your requirements.

## Contributing

Contributions are welcome! Please feel free to open issues or pull requests.



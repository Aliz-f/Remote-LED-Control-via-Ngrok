
# Remote LED Control via Ngrok
[FinalProject.pdf](https://github.com/Aliz-f/Esp8266_Internet-of-things/files/6796162/FinalProject.pdf)

This project allows you to control an LED remotely over the internet using an ESP8266/ESP32 Wi-Fi module and the Ngrok service. By creating a web server on the module and tunneling it through Ngrok, you can access and control the LED from a public URL, making it accessible from anywhere with an internet connection.

## Project Overview
The project includes:
- Setting up the ESP8266/ESP32 module in **Station mode** to connect to an ADSL modem.
- Creating a web server on the ESP8266/ESP32 to control the LED.
- Using Ngrok to create a secure tunnel to the local web server, enabling remote access via a public URL.

## Hardware Requirements
- ESP8266/ESP32 Wi-Fi Module
- LED
- Resistor (220Ω or appropriate value for the LED)
- Breadboard and jumper wires
- ADSL modem with internet access

## Software Requirements
- Arduino IDE
- Ngrok (Download from [https://ngrok.com/download](https://ngrok.com/download))

## Setup Instructions
1. **Configure the ESP8266/ESP32:**
   - Connect the LED to the module (e.g., GPIO pin D1) with a resistor in series.
   - Upload the Arduino code to the module, setting it up to operate as a web server.

2. **Install and Set Up Ngrok:**
   - Download and install Ngrok.
   - Start Ngrok to create a tunnel to the local web server:
     ```
     ngrok http 80
     ```
   - Note the public URL provided by Ngrok.

3. **Access the Web Interface:**
   - Open the public URL in your browser.
   - Use the interface to turn the LED on and off remotely.

## How It Works
- The ESP8266/ESP32 module sets up a web server that listens for HTTP requests.
- Using the Ngrok tunnel, the local web server is exposed to the internet.
- From the provided public URL, you can send commands to the module to control the LED.

## Optional Extension
- Control a 220V light via a relay module connected to the ESP8266/ESP32.


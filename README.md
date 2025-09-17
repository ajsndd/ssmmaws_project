# Amy's-stps-project -> ssmmaws
  Smart Soil Moisture Monitoring and Automatic Watering System
### Objective
  Design a system that continuously monitors the moisture level of the soil and automatically waters the plant when moisture falls below a specific threshold.

## 📂 Project Structure
```
ssmmaws_project/
└── ssmmaws_avg.ino    # Arduino project
```
## ▦ Components Needed
### 1. 🖱️ Hardware:
  * Microcontroller: Arduino Uno / ESP32 / Raspberry Pi Pico
  * Soil Moisture Sensor: Capacitive sensor (better than resistive due to durability)
  * Water Pump: 5V/12V mini water pump (submersible)
  * Relay Module or Transistor circuit (to control the pump)
  * Water Source: Small tank or bottle
  * Power Supply: Battery or adapter (based on microcontroller and pump)
		
	#### * Optional:
	* LCD / OLED Display (for live data)
	* Wi-Fi module (e.g., ESP8266/ESP32) for IoT capabilities
	* Buzzer or LED for alerts
	* Real-Time Clock (RTC) module for logging time-based data

	
 ### 2. 💻 Software:
 * Arduino IDE / MicroPython (for ESP32/Pico)	

	#### * Optional:
	* Blynk
 	* Firebase
  	* Thingspeak (for remote monitoring)

## ▶️ Working Principle
Soil moisture sensor is inserted into the soil.

The sensor outputs a voltage based on soil moisture (lower voltage = wetter soil).

The microcontroller reads the sensor data and compares it to a threshold value.

If soil is too dry, it triggers the water pump through a relay.

The system waters the soil for a fixed time or until moisture level is acceptable.

Optionally logs the data or sends it to the cloud.

### ➡️ Workflow
[Soil Sensor] --> [Microcontroller] --> [Decision Logic] --> [Relay] --> [Pump]
													  --> [Cloud/App] (optional)

## 👨‍💻 Author
- [AJEESH SAHADEVAN](https://github.com/ajsndd)  

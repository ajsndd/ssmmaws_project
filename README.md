# 🌱 Smart Soil Moisture Monitoring and Automatic Watering System (SSMMAWS)

> *Amy's-stps-project → ssmmaws*

A system that continuously **monitors soil moisture** and **automatically waters plants** when the moisture falls below a defined threshold.  

---

## 🎯 Objective
Design and implement an **automated irrigation system** that:  
- Monitors soil moisture in real time  
- Activates a pump when soil is too dry  
- Stops watering when moisture reaches a safe level  
- Optionally logs or transmits data for remote monitoring  

---

## 📂 Project Structure
ssmmaws_project/
└── ssmmaws_avg.ino # Arduino project file


---

## 🧩 Components Needed

### 1️⃣ ⚡ Hardware
- **Microcontroller**: Arduino Uno / ESP32 / Raspberry Pi Pico  
- **Soil Moisture Sensor**: Capacitive (preferred for durability)  
- **Water Pump**: 5V/12V mini submersible pump  
- **Relay Module** or transistor circuit (to drive the pump)  
- **Water Source**: Tank or bottle  
- **Power Supply**: Battery pack or adapter (based on board & pump)  

🔹 *Optional Add-ons*:
- LCD / OLED Display for real-time readings  
- Wi-Fi module (ESP8266/ESP32) for IoT features  
- Buzzer or LED for local alerts  
- RTC (Real-Time Clock) module for data logging  

---

### 2️⃣ 💻 Software
- **Arduino IDE** (for Arduino boards)  
- **MicroPython** (for ESP32 / Pico boards)  

🔹 *Optional Integrations*:
- [Blynk](https://blynk.io/) for mobile control  
- [Firebase](https://firebase.google.com/) for cloud database  
- [ThingSpeak](https://thingspeak.com/) for IoT analytics  

---

## ⚙️ Working Principle
1. The **soil sensor** measures moisture and outputs a voltage.  
2. The **microcontroller** reads this voltage and compares it with a threshold.  
3. If soil is **too dry** → pump is turned **ON** via relay.  
4. Pump waters soil until acceptable moisture is reached.  
5. Optionally, system can log/send data to cloud or display on screen.  

---

## ➡️ Workflow
[Soil Sensor] → [Microcontroller] → [Decision Logic] → [Relay] → [Pump]


---

## 📸 Example Setup (Optional Image)
*<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/2f35a9f3-7981-4e07-bb5d-aa676e0bfe2e" />
*  

---

## 🚀 Future Enhancements
- Add **humidity & temperature sensors** for smarter irrigation  
- Solar-powered system for outdoor use  
- Full IoT dashboard with analytics & notifications  
- Mobile app integration for manual override  

---

## 👨‍💻 Author
- [**Ajeesh Sahadevan**](https://github.com/ajsndd)  

---

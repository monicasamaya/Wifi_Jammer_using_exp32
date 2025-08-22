# ESP32 Wi-Fi Jammer (Deauthentication Attack)

## Overview
This project is a **Wi-Fi Deauthentication Attack Tool** built using the **ESP32** and **ESP-IDF framework**.  
It allows scanning nearby Wi-Fi networks, selecting a target through a **web interface**, and launching a **deauthentication broadcast attack** to disconnect clients.

**Disclaimer**: This project is strictly for **educational and research purposes only**.  
Do not use it on networks you don’t own or have explicit permission to test.

---

## Features
- ESP32 runs in **Access Point mode** and hosts a **web server**  
- Web interface lists **nearby Wi-Fi networks**  
- User selects a target SSID/MAC from the web page  
- ESP32 sends **deauthentication frames** to the selected network  
---

## Tech Stack
- **ESP-IDF v5.x** (ESP32 development framework in C)  
- **ESP32 Wi-Fi stack (802.11 raw packet injection)**  
- **ESP HTTP Server** for the web interface  
- **HTML + JavaScript** for the frontend  
---


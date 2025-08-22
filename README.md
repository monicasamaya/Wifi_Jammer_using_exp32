# ESP32 Wi-Fi Jammer (Deauthentication Attack)

## About the project
This project is a **Wi-Fi Deauthentication Attack Tool** built on the ESP32 using the ESP-IDF framework. The ESP32 operates as an Access Point, hosts a web interface, scans nearby Wi-Fi networks, and allows the user to select a target to **launch a deauthentication broadcast attack** by sending crafted IEEE 802.11 frames to disconnect clients. I implemented the system by designing the deauth attack logic in C, building a custom web server with ESP-IDF, integrating Wi-Fi scanning to list available networks, and ensuring smooth interaction between the web interface and the attack engine. The project was developed to explore wireless security vulnerabilities, gain hands-on experience in low-level Wi-Fi packet manipulation, and demonstrate a complete end-to-end solution combining embedded programming, networking, and web technologies.

---
## Motivation
The motivation behind this project was to understand Wi-Fi security at a deeper level by practically implementing an attack that exploits the IEEE 802.11 protocol. While Wi-Fi deauthentication attacks are widely known, building the tool from scratch on the ESP32 gave me hands-on experience with raw packet crafting, embedded system programming, and real-time web interfaces. This project also strengthened my skills in ESP-IDF development, debugging, and networking concepts, while highlighting the importance of securing wireless networks against such vulnerabilities.
**Disclaimer**: This project is strictly for **educational and research purposes only**. 

---
## Software Details
- **ESP-IDF v5.x** – official development framework for ESP32, used to build and flash the firmware  
- **C Programming Language** – for implementing Wi-Fi scanning, web server, and deauthentication logic  
- **ESP32 Wi-Fi Stack (802.11)** – to enable raw packet injection and deauth frame crafting  
- **ESP HTTP Server** – lightweight web server library provided by ESP-IDF for hosting the web interface  
- **HTML + JavaScript** – for designing the front-end webpage that displays scanned networks and triggers attacks  
- **Serial Monitor (idf.py monitor / PuTTY / Arduino Serial Monitor)** – for debugging and observing logs  

--
## Future works
-Add support for multiple attack types (Beacon Flood, Probe Flood, etc.)  
- Enhance the web interface with a mobile-friendly design and real-time attack status  
- Implement logging of scanned networks and attack history   
- Add authentication to the web interface for safer usage  

---
## Legal Disclaimer  

This project is created strictly for **educational and research purposes only**.  
Performing Wi-Fi jamming or deauthentication attacks on networks that you do not own or do not have explicit permission to test is **illegal** and may lead to severe consequences.  
The author is **not responsible for any misuse or damage** caused by this project.  
Use this tool responsibly and only in controlled environments where you have full authorization.  


## Overview
The **WiFi Controller** module manages all low-level Wi-Fi operations for the ESP32 in this project.It is responsible for initializing the Wi-Fi stack, scanning nearby networks, tuning to specific channels,  
and enabling raw packet injection needed for attacks. This module acts as the bridge between the high-level attack logic and the ESP32’s 802.11 radio.

---
## Responsibilities
- **Wi-Fi Initialization** – Configures ESP32 Wi-Fi in AP/STA/dual mode using ESP-IDF APIs.  
- **Channel Control** – Tunes the radio to a specific Wi-Fi channel ('esp_wifi_set_channel'), enabling targeted attacks.  
- **Scanning** – Performs active/passive scans to detect SSIDs, BSSIDs, RSSI, and channels of nearby access points.  
- **Sniffing** – Uses promiscuous mode to capture raw 802.11 frames (beacons, probes, data).  
- **Packet Injection** – Transmits crafted raw management frames (deauthentication) with 'esp_wifi_80211_tx'.  
- **Mode Switching** – Handles switching between serving the web interface (AP mode) and executing attacks (attack mode).  

--- 

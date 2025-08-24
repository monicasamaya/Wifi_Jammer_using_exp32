## Overview
The **Webserver** module provides the user interface for controlling and monitoring the ESP32 Wi-Fi jammer.It runs an HTTP server in AP mode, allowing clients to connect to the ESP32’s access point  and interact with a web-based control panel. This UI displays scanned networks, accepts target selections, and triggers attack commands that are forwarded to the WiFi Controller and Attack modules.

---
## Responsibilities
- **Access Point Hosting** – Configures the ESP32 as a Wi-Fi Access Point so users can connect directly.  
- **HTTP Server** – Hosts web pages.  
- **UI Delivery** – Serves HTML, CSS, and JavaScript files to create an interactive control panel.  
- **Network Display** – Presents scanned SSID/BSSID/channel data retrieved from the WiFi Controller.  
- **Command Handling** – Accepts POST/JSON requests from the UI (e.g., target network selection, start/stop attack).  

---


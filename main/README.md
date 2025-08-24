## Technical Background  
This project demonstrates a **Wi-Fi Deauthentication Attack** using the ESP32 and the ESP-IDF framework.  
It exploits a vulnerability in the **IEEE 802.11 Wi-Fi protocol**, where management frames such as deauthentication are unauthenticated in older standards.  
- By crafting and transmitting **fake deauthentication frames**, the ESP32 makes client devices believe the Access Point (AP) has disconnected them.  
- The ESP32 switches to the target AP’s channel and repeatedly injects raw packets containing the AP’s BSSID.  
- Nearby clients connected to that AP are forcibly disconnected. 

### Execution Flow  
1. **Event Loop Creation** → esp_event_loop_create_default()' sets up the global event handler system.  
2. **Management Access Point Start** → 'wifictl_mgmt_ap_start()' creates a control hotspot 'WiFi-Jammer' where the user connects (default IP 192.168.4.1).  
3. **Attack Module Initialization** → 'attack_init()' prepares the attack subsystem (timers, logging).  
4. **Webserver Launch** → 'webserver_run()' starts an HTTP server which provides the web interface and accepts attack commands.  
5. **Attack Trigger** → when the user clicks "Start Attack" in the UI, a JSON request ('BSSID', 'Channel') is sent to '/attack'.  
6. **Attack Execution** → request is forwarded from 'webserver.c' → 'attack.c' → 'attack_method.c', where deauthentication frames are crafted and repeatedly sent via 'esp_timer' and 'esp_wifi_80211_tx()'.  

    The main module initializes the system, hosts the control interface, and delegates attack execution to lower-level modules.  

---
## Files in This Folder  

### 'main.c'
Entry point of the firmware. Starts event loop, brings up management AP (`WiFi-Jammer`), initializes attack logic, and launches the webserver.  

### 'attack.c'  
High-level attack manager. Provides functions to initialize attacks and forward requests to low-level methods.   

### 'attack_method.c' 
Implements the **deauthentication attack logic**. Crafts raw 802.11 deauthentication frames, sets the Wi-Fi channel, and periodically transmits them using ESP32 timers.  

---
## Disclaimer    
Running deauthentication attacks on networks you do not own or have explicit permission to test is **illegal** and may result in severe penalties.  

---


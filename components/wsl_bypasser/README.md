## Overview
The **WSL Bypasser** module provides a wrapper around raw 802.11 frame injection functions. It bypasses ESP-IDF internal checks that may prevent sending crafted frames in certain environments  
(e.g., when compiling under WSL). This module ensures that custom management frames such as  
**deauthentication frames** can be transmitted reliably by the ESP32.

---
## Responsibilities
- Implements a **sanity check override** to always allow raw frame injection.  
- Provides an API to **send arbitrary raw 802.11 frames**`.  
- Constructs and transmits **default deauthentication frames** targeted at a given AP BSSID.  


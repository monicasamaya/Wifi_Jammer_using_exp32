#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include <stdint.h>
#include <unistd.h>

#include "esp_wifi_types.h"
#include "ap_scanner.h"

// Starts the custom management access point (ManagementAP)
void wifictl_mgmt_ap_start();

// SoftAP management
void wifictl_ap_start(wifi_config_t *wifi_config);
void wifictl_ap_stop();

// STA mode connection management
void wifictl_sta_connect_to_ap(const wifi_ap_record_t *ap_record, const char password[]);
void wifictl_sta_disconnect();

// MAC address operations
void wifictl_set_ap_mac(const uint8_t *mac_ap);
void wifictl_get_ap_mac(uint8_t *mac_ap);
void wifictl_restore_ap_mac();
void wifictl_get_sta_mac(uint8_t *mac_sta);

// Channel setting
void wifictl_set_channel(uint8_t channel);

// Get scan results from AP scanner
const wifi_ap_record_t *wifictl_get_ap_record(uint8_t id);

#endif // WIFI_CONTROLLER_H

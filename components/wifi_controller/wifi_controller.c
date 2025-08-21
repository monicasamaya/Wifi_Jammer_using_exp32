#include <string.h>
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "wifi_controller.h"

#define MGMT_WIFI_SSID "WiFi-Jammer"
#define MGMT_WIFI_PASSWORD "12345678"

#define MAX_APs 20

static wifi_ap_record_t ap_records[MAX_APs];
static uint16_t ap_count = 0;
static const char *TAG = "wifi_controller";

// Event handler
static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI(TAG, "Station " MACSTR " joined, AID=%d", MAC2STR(event->mac), event->aid);

    }
}

void wifictl_mgmt_ap_start(void)
{
    // Initialize TCP/IP and Wi-Fi
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register event handler
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = MGMT_WIFI_SSID,
            .ssid_len = strlen(MGMT_WIFI_SSID),
            .channel = 1,
            .password = MGMT_WIFI_PASSWORD,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    if (strlen(MGMT_WIFI_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Management AP started. Connect to SSID: %s", MGMT_WIFI_SSID);
}

// Scan nearby APs
uint8_t wifictl_scan_start(void)
{
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true
    };

    esp_wifi_scan_start(&scan_config, true);
    esp_wifi_scan_get_ap_records(&ap_count, ap_records);

    ESP_LOGI(TAG, "Found %d APs", ap_count);
    return ap_count;
}

const wifi_ap_record_t *wifictl_get_ap_record(uint8_t id)
{
    if (id >= ap_count) return NULL;
    return &ap_records[id];
}

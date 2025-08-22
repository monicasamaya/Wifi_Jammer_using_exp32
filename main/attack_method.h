#ifndef ATTACK_METHOD_H
#define ATTACK_METHOD_H

#include <stdint.h>
#include "esp_wifi.h"

void start_deauth_attack(uint8_t target_mac[6], uint8_t channel);

#endif

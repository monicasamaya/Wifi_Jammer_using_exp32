#ifndef ATTACK_H
#define ATTACK_H
#include <stdint.h>

void launch_deauth_attack(uint8_t *bssid, uint8_t channel);
void attack_init(void);
#endif

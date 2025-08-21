#ifndef SNIFFER_H
#define SNIFFER_H

#include <stdint.h>

void sniffer_set_channel(uint8_t channel);
void wifi_sniffer_send_packet(const void *buffer, uint16_t len);

#endif

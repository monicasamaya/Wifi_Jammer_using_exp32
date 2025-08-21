#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "esp_event.h"
#include "esp_http_server.h"

// Events emitted by the HTTP server
ESP_EVENT_DECLARE_BASE(WEBSERVER_EVENTS);
enum {
    WEBSERVER_EVENT_ATTACK_REQUEST, // Payload = attack_request_t
    WEBSERVER_EVENT_ATTACK_RESET    // No payload
};

// HTTP → application handshake
typedef struct {
    uint8_t ap_record_id; // index into the last scan
    uint8_t timeout;      // seconds
} attack_request_t;

// Launch the async web server (calls esp_http_server_start internally)
void webserver_run(void);

#endif // WEBSERVER_H

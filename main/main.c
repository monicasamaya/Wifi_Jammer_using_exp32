#include "esp_event.h"
#include "wifi_controller.h"
#include "attack.h"
#include "webserver.h"

void app_main(void)
{
    // Create default event loop
    esp_event_loop_create_default();

    // Bring up the management AP so you can connect your PC to 192.168.4.1
    wifictl_mgmt_ap_start();

    // Initialize attack subsystem (timers + event handlers)
    attack_init();

    // Start the HTTP server and handlers
    webserver_run();
}

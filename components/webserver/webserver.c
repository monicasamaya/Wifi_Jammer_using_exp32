#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"
#include "attack.h"

static const char *TAG = "webserver";

/* POST handler for /attack */
esp_err_t attack_post_handler(httpd_req_t *req) {
    char content[256];
    int ret = httpd_req_recv(req, content, (req->content_len < sizeof(content) - 1) ? req->content_len : sizeof(content) - 1);
    if (ret <= 0) {
        return ESP_FAIL;
    }
    content[ret] = '\0';

    ESP_LOGI(TAG, "Received JSON: %s", content);

    cJSON *root = cJSON_Parse(content);
    if (!root) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    cJSON *bssid_json = cJSON_GetObjectItem(root, "bssid");
    cJSON *channel_json = cJSON_GetObjectItem(root, "channel");

    if (!bssid_json || !cJSON_IsString(bssid_json) ||
        !channel_json || !cJSON_IsNumber(channel_json)) {
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing fields");
        return ESP_FAIL;
    }

    const char *bssid_str = bssid_json->valuestring;
    uint8_t bssid[6];
    if (sscanf(bssid_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
               &bssid[0], &bssid[1], &bssid[2],
               &bssid[3], &bssid[4], &bssid[5]) != 6) {
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid BSSID format");
        return ESP_FAIL;
    }

    uint8_t channel = (uint8_t)channel_json->valueint;

    ESP_LOGI(TAG, "Starting attack on BSSID: %s, Channel: %d", bssid_str, channel);
    launch_deauth_attack(bssid, channel);

    httpd_resp_sendstr(req, "Attack started");
    cJSON_Delete(root);
    return ESP_OK;
}

httpd_handle_t webserver_run(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t attack_uri = {
            .uri       = "/attack",
            .method    = HTTP_POST,
            .handler   = attack_post_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &attack_uri);
    }
    return server;
}

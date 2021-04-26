#include "./wifi.h"

using namespace std;

static void event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        printf("Kite connected.\n");
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        printf("Kite disconnected.\n");
    }
}

void init_wifi (wifi_ap_config_t config) {

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        nullptr,
                                                        nullptr));

    esp_wifi_set_protocol(WIFI_IF_AP, WIFI_PROTOCOL_LR);
    wifi_config_t wifi_config = {
            .ap = config,
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("Ready to accept connections.\n");
}
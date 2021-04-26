#include <dirent.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "helpers/wifi.h"

extern "C" _Noreturn void app_main(void) {

    nvs_flash_init(); // Required for WiFi at least.

    wifi_ap_config_t wifi_config {
        "KiteReceiver",
        "KiteReceiver",
        .channel = 1,
        .authmode = WIFI_AUTH_WPA_WPA2_PSK,
        .ssid_hidden = 0,
        .max_connection = 1,
    };
    init_wifi(wifi_config);

    while (1) {
        vTaskDelay(100);
        printf("Running\n");
    }
}

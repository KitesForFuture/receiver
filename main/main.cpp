#include <dirent.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_crc.h"
#include <esp_vfs_dev.h>

static const char* FLYDATA = "FLYDATA";

static void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len)
{
    fwrite(FLYDATA, 1, 7, stdout);
    fwrite(data, len, 1, stdout);
    fflush(stdout);
}

extern "C" _Noreturn void app_main(void) {

    uint8_t mac [6];
    esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);
    printf("MAC Address: %i %i %i %i %i %i \n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    nvs_flash_init();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );
    ESP_ERROR_CHECK( esp_wifi_start());
    ESP_ERROR_CHECK( esp_wifi_set_protocol(static_cast<wifi_interface_t>(ESP_IF_WIFI_AP), WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N | WIFI_PROTOCOL_LR) );
    ESP_ERROR_CHECK( esp_now_init() );

    ESP_ERROR_CHECK( esp_now_register_recv_cb(on_data_recv) );

    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_LF);
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_LF);

    while (1) {
        vTaskDelay(1);
    }
}

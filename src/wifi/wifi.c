#include "wifi/wifi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

void wifi_task(void *pvParameters) {
    printf("Starting WTTR.in Pico W client...\n");

    if (cyw43_arch_init())
    {
        printf("Failed to initialise CYW43\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                              CYW43_AUTH_WPA2_AES_PSK, 10000)) {
                printf("Wi-Fi connect failed, retrying...\n");
                vTaskDelay(pdMS_TO_TICKS(5000));
            }
    xEventGroupSetBits(wifi_group, 0x01);
    printf("Wi-Fi connected!\n");

    while (true) {
        if (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP) {
            xEventGroupClearBits(wifi_group, 0x01);
            printf("Wi-Fi was lost, attempting to reconnect..\n");
            while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                              CYW43_AUTH_WPA2_AES_PSK, 30000)) {
                printf("Reconnecting failed, trying a few more times..\n");
                vTaskDelay(pdMS_TO_TICKS(5000));
            }
            xEventGroupSetBits(wifi_group, 0x01);
            printf("Wi-Fi reconnected!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
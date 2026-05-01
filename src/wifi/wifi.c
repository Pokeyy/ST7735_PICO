#include "wifi/wifi.h"

int wifi_connect() {
    printf("Starting WTTR.in Pico W client...\n");

    if (cyw43_arch_init())
    {
        printf("Failed to initialise CYW43\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                              CYW43_AUTH_WPA2_AES_PSK, 10000))
            {
                printf("Wi-Fi connect failed, retrying...\n");
                sleep_ms(5000);
            }

    printf("Wi-Fi connected!\n");

}
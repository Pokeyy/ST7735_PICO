#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "include/hardware.h"
#include "include/ST7735_TFT.h"
#include "include/ST7735_Screens.h"
#include "demos/RTC/rtc.h"
#include "ST7735_Screens.h"
#include "weather.h"
#include "pico/cyw43_arch.h"


#define BUTTON 14

int led_value = 0;

bool repeating_timer_callback(struct repeating_timer *t) {
    led_value = 1 - led_value;
    gpio_put(25, led_value);
    printf("LED Toggled\n");

    return true;
}

void button_callback(uint gpio, uint32_t events) {
    led_value = 1 - led_value;
    gpio_put(25, led_value);
}

int the_weather() {
    int temp;
    char temp_str[16];
    sleep_ms(3000);
    printf("Starting WTTR.in Pico W client...\n");

    if (cyw43_arch_init()) {
        printf("Failed to initialise CYW43\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    // Connect to Wi-Fi
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Wi-Fi connect failed, retrying in 5s...\n");
        sleep_ms(WIFI_RETRY_DELAY_MS);
    }
    printf("Wi-Fi connected!\n");

    // Give lwIP time to initialize DNS
    sleep_ms(2000);

    while (true) {
        int attempt = 0;
        int result = 4; // Start assuming DNS failure
        while (result == 4 && attempt < 5) {
            printf("Fetching weather, attempt %d...\n", attempt+1);
            result = fetch_weather(&temp);
            // if (temp != -1) {
                snprintf(temp_str, sizeof(temp_str), "%dF", temp);
                draw_string(10, 20, temp_str, ST7735_BLACK, ST7735_WHITE, 2);
            // }
            if (result == 4) {
                printf("DNS failed, retrying in 5s...\n");
                sleep_ms(WIFI_RETRY_DELAY_MS);
                attempt++;
            }
        }

        if (result != 0) {
            printf("Request failed with code %d\n", result);
        } else {
            printf("Request successful!\n");
        }

        printf("Sleeping for 30 minutes...\n\n");
        sleep_ms(FETCH_INTERVAL_MS);
    }

    cyw43_arch_deinit();
    return 0;
}

int main() {
    stdio_init_all();
    sleep_ms(50); // small delay
    while(!stdio_usb_connected()) {
        tight_loop_contents();
    }
    sleep_ms(50);
    
    
    st7735_spi_init();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);


    st7735_init_display();
    set_rotation(ROTATION_90); //
    fill_screen(ST7735_WHITE);

    sleep_ms(1500);

    the_weather();
}

int main1()
{
    stdio_init_all();
    sleep_ms(50); // small delay
    while(!stdio_usb_connected()) {
        tight_loop_contents();
    }
    sleep_ms(50);
    
    
    st7735_spi_init();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);


    st7735_init_display();
    set_rotation(ROTATION_90); //
    fill_screen(ST7735_WHITE);

    sleep_ms(1500);
    draw_weather_screen();

    // //sleep_ms(1000);
    // draw_char(3, 3, 'A', ST7735_BLACK, ST7735_WHITE, 1);
    // draw_char(10, 3, 'B', ST7735_BLACK, ST7735_WHITE, 1);
    // draw_char(17, 3, 'C', ST7735_BLACK, ST7735_WHITE, 1);

    // draw_string(3, 10, "Nguyen Method", ST7735_BLUE, ST7735_WHITE, 2);

    // set_rotation(ROTATION_270);
    // //sleep_ms(1000);
    // draw_char(3, 3, 'A', ST7735_BLACK, ST7735_WHITE, 1);
    // draw_char(10, 3, 'B', ST7735_BLACK, ST7735_WHITE, 1);
    // draw_char(17, 3, 'C', ST7735_BLACK, ST7735_WHITE, 1);

    // draw_string(3, 10, "Nguyen Method", ST7735_BLUE, ST7735_WHITE, 2);
    // sleep_ms(2500);
    // fill_screen(ST7735_WHITE);

    // sleep_ms(2000);

    // draw_bitmap(75, 55, ICON_WEATHER_SUN, ST7735_YELLOW, ST7735_WHITE, 3);

    // sleep_ms(2000);
    // draw_bitmap(35, 80, ICON_WEATHER_CLOUD, ST7735_GRAY_LIGHT, ST7735_WHITE, 3);
    // draw_bitmap(60, 80, ICON_WEATHER_CLOUD, ST7735_GRAY_MEDIUM, ST7735_WHITE, 3);
    // draw_bitmap(85, 80, ICON_WEATHER_CLOUD, ST7735_GRAY_DARK, ST7735_WHITE, 3);
    // draw_bitmap(110, 80, ICON_WEATHER_CLOUD, ST7735_BLACK, ST7735_WHITE, 3);

    while (true) {

    // Or just keep it tight loop if you don't want LED blinking:
    tight_loop_contents();
    }




}

        //aon_timer_read();
    //ao_timer_demo();
    // gpio_init(BUTTON);
    // gpio_set_dir(BUTTON, GPIO_IN);
    // gpio_pull_up(BUTTON);
    // gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, 1, button_callback); // falling edge for interrupt, rising edge is 0x08

    //repeating_timer_t timer;
    //add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);
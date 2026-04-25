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

int the_weather()
{
    int temps_max[3], temps_min[3];
    char temp_str[16];

    sleep_ms(3000);
    printf("Starting WTTR.in Pico W client...\n");

    if (cyw43_arch_init())
    {
        printf("Failed to initialise CYW43\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                              CYW43_AUTH_WPA2_AES_PSK, 30000))
            {
                printf("Wi-Fi connect failed, retrying...\n");
                sleep_ms(5000);
            }

    printf("Wi-Fi connected!\n");

    sleep_ms(2000);

    while (true)
    {
        if( cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) != CYW43_LINK_UP) {
            printf("WiFi lost, reconnecting...\n");
            while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                              CYW43_AUTH_WPA2_AES_PSK, 30000))
            {
                printf("Reconnecting failed, retrying...\n");
                sleep_ms(5000);
            }
            printf("Reconnected!\n");
        }

        int attempt = 0;
        int result = -1;


        draw_string(5, 5, "Updating...", ST7735_BLACK, ST7735_WHITE, 1);
        while (attempt < 5)
        {
            result = fetch_weather(temps_max, temps_min);
            if (result == WEATHER_OK)
                break;
            attempt++;
            if (attempt < 5) sleep_ms(2000); // only sleep if actually retrying
        }
        draw_string(5, 5, "           ", ST7735_BLACK, ST7735_WHITE, 1);

        if (result == WEATHER_OK)
        {
            for (int i = 0; i < 3; i++)
            {
                char line[24];
                snprintf(line, sizeof(line), "D%d %dF/%dF", i+1, temps_max[i], temps_min[i]);
                draw_string(5, 20 + (i * 20), line, ST7735_BLACK, ST7735_WHITE, 1);
            }
        }
        else
        {
            switch (result) {
                case WEATHER_ERR_HTTP:    printf("HTTP request failed\n");   break;
                case WEATHER_ERR_NO_JSON: printf("No JSON in response\n");   break;
                case WEATHER_ERR_PARSE:   printf("JSON parse failed\n");     break;
                case WEATHER_ERR_MISSING: printf("Missing expected field\n"); break;
            }
        }

        printf("Sleeping...\n\n");
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
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "drivers/ST7735_TFT.h"
//#include "demos/RTC/rtc.h"
#include "weather/weather.h"
#include "pico/cyw43_arch.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "wifi/wifi.h"

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
    printf("task creating.. \n");

    wifi_group = xEventGroupCreate();

    if (wifi_group == NULL) {
        panic("Not enough heap space. Initiating panic and halting execution!!\n");
    }
    else {
        printf("Event group for Wi-Fi task created successfully!\n");
    }


    BaseType_t wifi_task = xTaskCreate(wifi_task, "WiFiTask", 4096, NULL, 1, NULL);
    BaseType_t result = xTaskCreate(weather_task, "WeatherTask", 4096, NULL, 1, NULL);
    printf("xTaskCreate result: %d\n", result);  // 1 = success
    printf("task created, starting scheduler\n");
    vTaskStartScheduler();
    while(true);
}
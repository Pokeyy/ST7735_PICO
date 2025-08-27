#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "include/hardware.h"
#include "include/ST7735_TFT.h"
#include "include/test.h"
#include "demos/RTC/rtc.h"


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

int main()
{
    stdio_init_all();
    sleep_ms(500); // small delay
    while(!stdio_usb_connected()) {}  // waits for USB serial to be connected
    st7735_spi_init();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    st7735_init_display();
    fill_screen(ST7735_WHITE);

    sleep_ms(1000);

    //aon_timer_read();
    ao_timer_demo();

    // while (1) {
    //     tight_loop_contents();          // makes sure timers, interrupts and callbacks are called on time
    // }


}

    // gpio_init(BUTTON);
    // gpio_set_dir(BUTTON, GPIO_IN);
    // gpio_pull_up(BUTTON);
    // gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, 1, button_callback); // falling edge for interrupt, rising edge is 0x08

    //repeating_timer_t timer;
    //add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);
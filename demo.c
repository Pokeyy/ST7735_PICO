#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "include/hardware.h"
#include "include/ST7735_TFT.h"

// To Do List:
// Understand timings for each pin change of SPI
// Understand power commands maybe
// Make sure that screen works with ST7735.c and the other files
// Organize CMake and project for differing screen types


int main()
{
    stdio_init_all();
    st7735_spi_init();


    sleep_ms(50);
    gpio_put(SPI_ST7735_RST, 1);
    sleep_ms(50);

    st7735_init_display();
    fill_screen(ST7735_BLUE);

    sleep_ms(1000);
    for(int i = 33; i < 77; i++) {
        draw_pixel(i, 55, ST7735_GREEN);
    }
}
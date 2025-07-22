#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "include/hardware.h"
#include "include/ST7735_TFT.h"

// To Do List:
// Understand timings still for each pin change of SPI
// Understand power commands maybe
// Make sure that screen works with ST7735.c and the other files
// Organize CMake and project for differing screen types



void test1(const st7735_pin_config_t *pins) {
        // Set full screen window
    write_command(pins, ST77XX_CASET);
    write_data(pins, 0x00); write_data(pins, 0x00);   // X start 1 - offsetted
    write_data(pins, 0x00); write_data(pins, 0x7F);   // X end (160) - offsetted

    write_command(pins, ST77XX_RASET);
    write_data(pins, 0x00); write_data(pins, 0x00);   // Y start 2 - offsetted
    write_data(pins, 0x00); write_data(pins, 0x9F);   // Y end (129) - offsetted

    write_command(pins, ST77XX_RAMWR);

    // Fill with black
    uint8_t black_pixel[2] = {0x00, 0x00};
    for (int i = 0; i < 160 * 128; i++) {
        write_data_buffer(pins, black_pixel, 2);
    }

    // CASET (COlumn address set)
    write_command(pins, ST77XX_CASET);

    // Start position (X)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x12);                  // lower byte

    // End Position (X)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x14);                  // lower byte

    // RASET (row address set)
    write_command(pins, ST77XX_RASET);

    // Start position (Y)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x11);                  // lower byte 

    // End Position (Y)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x13);                  // lower byte


    write_command(pins, ST77XX_RAMWR);
    

    uint8_t color[2] = {0xF8, 0x00}; // red
    uint8_t buffer[3*3*2];
    for(int i = 0; i < 3*3; i++) {
        buffer[i*2] = color[0];
        buffer[i * 2 + 1] = color[1];
    }
    write_data_buffer(pins, buffer, sizeof(buffer));

    /////////////////////////
        // CASET (COlumn address set)
    write_command(pins, ST77XX_CASET);

    // Start position (X)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x50);                  // lower byte

    // End Position (X)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x52);                  // lower byte

    // RASET (row address set)
    write_command(pins, ST77XX_RASET);

    // Start position (Y)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x11);                  // lower byte 

    // End Position (Y)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x13);                  // lower byte


    write_command(pins, ST77XX_RAMWR);
    

    uint8_t color1[2] = {0xF8, 0x00}; // red
    uint8_t buffer1[3*3*2];
    for(int i = 0; i < 3*3; i++) {
        buffer1[i*2] = color[0];
        buffer1[i * 2 + 1] = color[1];
    }
    write_data_buffer(pins, buffer1, sizeof(buffer1));



    ////////////////////////////////////////////////////////

        // CASET (COlumn address set)
    write_command(pins, ST77XX_CASET);

    // Start position (X)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x03);                  // lower byte

    // End Position (X)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x57);                  // lower byte

    // RASET (row address set)
    write_command(pins, ST77XX_RASET);

    // Start position (Y)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x60);                  // lower byte 

    // End Position (Y)
    write_data(pins, 0x00);                  // upper byte
    write_data(pins, 0x62);                  // lower byte


    write_command(pins, ST77XX_RAMWR);
    

    uint8_t color2[2] = {0xF8, 0x00}; // red
    uint8_t buffer2[89*3*2];
    for(int i = 0; i < 89*3; i++) {
        buffer2[i*2] = color[0];
        buffer2[i * 2 + 1] = color[1];
    }
    write_data_buffer(pins, buffer2, sizeof(buffer2));

    sleep_ms(2000);
    while(1);
}


int main()
{
    stdio_init_all();
    st7735_spi_init();


    sleep_ms(50);
    gpio_put(SPI_ST7735_RST, 1);
    sleep_ms(50);

    st7735_init_display();
    fill_screen(ST7735_RED);
}
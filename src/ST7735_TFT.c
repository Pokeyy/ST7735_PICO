#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware.h"
#include "ST7735_TFT.h"

// To Do List:
// Understand timings still for each pin change of SPI
// Understand power commands maybe
// Make sure that screen works with ST7735.c and the other files
// Update CMake to work with new files
// If not, just copy and paste into og files

st7735_pin_config_t interface_pins = {
    .cs_pin = SPI_ST7735_CS,
    .rs_pin = SPI_ST7735_RS,
    .rst_pin = SPI_ST7735_RST,
    .spi_port = SPI_ST7735_PORT
};

void write_command(const st7735_pin_config_t *pins, uint8_t cmd) {
    gpio_put(pins->rs_pin, 0);
    gpio_put(pins->cs_pin, 0);
    spi_write_blocking(pins->spi_port, &cmd, 1);
    gpio_put(pins->cs_pin, 1);
}

void write_data(const st7735_pin_config_t *pins, uint8_t data) {
    gpio_put(pins->rs_pin, 1);
    gpio_put(pins->cs_pin, 0);
    spi_write_blocking(pins->spi_port, &data, 1);
    gpio_put(pins->cs_pin, 1);
}

void write_data_buffer(const st7735_pin_config_t *pins, const uint8_t *data, size_t len) {
    gpio_put(pins->rs_pin, 1);
    gpio_put(pins->cs_pin, 0);
    spi_write_blocking(pins->spi_port, data, len);
    gpio_put(pins->cs_pin, 1);
}

void fill_screen(uint16_t color) {
    uint8_t upper = color >> 8;
    uint8_t lower = color & 0xFF; 
    uint8_t combined[2] = {upper, lower};
    
    write_command(&interface_pins, ST77XX_CASET);
    write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x00);   // X start 1 - offsetted
    write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x7F);   // X end (160) - offsetted

    write_command(&interface_pins, ST77XX_RASET);
    write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x00);   // Y start 2 - offsetted
    write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x9F);   // Y end (129) - offsetted

    write_command(&interface_pins, ST77XX_RAMWR);

    for (int i = 0; i < 160 * 128; i++) {
        write_data_buffer(&interface_pins, combined, 2);
    }

}

void st7735_init_display() {
    // Step 1, Reset it 
    write_command(&interface_pins, ST77XX_SWRESET);
    sleep_ms(120);

    // Wake display up
    write_command(&interface_pins, ST77XX_SLPOUT);
    sleep_ms(120);

    // Define Pixel Format (COLMOD)  - 12/16/18 bit
    write_command(&interface_pins, ST77XX_COLMOD);
    write_data(&interface_pins, 0x05);                 // 16-bit

    // MADCTL (define reading or writing each frame scan)
    write_command(&interface_pins, ST77XX_MADCTL);
    write_data(&interface_pins, 0xC0);                   // bits 0-4 just keep 0 for default, bits 5-7 indicate inversion, like if your first pixel starts opposite side
                                                         // (MX, MY, MV = 0) (was 0x00 before but adafruit uses 0xC0)

    // Normal Display Mode ON
    write_command(&interface_pins, ST77XX_NORON);
    sleep_ms(10);

    // Turn Display On
    write_command(&interface_pins, ST77XX_DISPON);
    sleep_ms(100);

}


// int main()
// {
//     stdio_init_all();

//     gpio_put(SPI_ST7735_LEDA, 0);
//     sleep_ms(50);
//     gpio_put(SPI_ST7735_LEDA, 1);

//     gpio_put(SPI_ST7735_RST, 0);
//     sleep_ms(50);
//     gpio_put(SPI_ST7735_RST, 1);

//     st7735_init_display(&interface_pins);
// }
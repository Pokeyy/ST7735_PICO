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

uint8_t col_start = 0, row_start = 0, x_start = 0, y_start = 0;

uint8_t tft_width = 128, tft_height = 160;

st7735_pin_config_t interface_pins = {
    .cs_pin = SPI_ST7735_CS,
    .rs_pin = SPI_ST7735_RS,
    .rst_pin = SPI_ST7735_RST,
    .spi_port = SPI_ST7735_PORT
};

void write_command(uint8_t cmd) {
    tft_rs_low();
    tft_cs_low();
    spi_write(cmd);
    tft_cs_high();
}


void write_data(uint8_t data) {
    tft_rs_high();
    tft_cs_low();
    spi_write(data);
    tft_cs_high();
}


void set_AddrArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    write_command(ST77XX_CASET);
    write_data(0); write_data(x0 + x_start);            // unsure about x_start, maybe for offset or some other func?
    write_data(0); write_data(x1 + x_start);

    write_command(ST77XX_RASET);
    write_data(0); write_data(y0 + y_start);            // unsure about y_start, maybe for offset or some other func?
    write_data(0); write_data(y1 + y_start);

    write_command(ST77XX_RAMWR);
}

void fill_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color) {
    uint8_t upper, lower;
    if( (x >= tft_width) || (y >= tft_height) )
        return;
    if( (x + width - 1) >= tft_width)
        width = tft_width - x;
    if( (y + height - 1) >= tft_height)
        height = tft_height - y;
    set_AddrArea(x, y, x+width-1, y+height-1);
    upper = color >> 8; lower = color;
    tft_rs_high();                                      // not using spi_write instantly to not spam loop pin changes
    tft_cs_low();
    for(y = height; y > 0; y--) {
        for (x = width; x > 0; x--) {
            spi_write(upper);
            spi_write(lower);
        }
    }
    tft_cs_high();
}

void fill_screen(uint16_t color) {
    fill_rectangle(0, 0, tft_width, tft_height, color);
}


void draw_pixel(uint8_t x, uint8_t y, uint16_t color) {
    if( (x >= disp_width) || y >= disp_height )
        return;
    // setAddrArea();
    //write_data()
}

void st7735_init_display() {
    // Step 1, Reset it 
    write_command(ST77XX_SWRESET);
    sleep_ms(120);

    // Wake display up
    write_command(ST77XX_SLPOUT);
    sleep_ms(120);

    // Define Pixel Format (COLMOD)  - 12/16/18 bit
    write_command(ST77XX_COLMOD);
    write_data(0x05);                 // 16-bit

    // MADCTL (define reading or writing each frame scan)
    write_command(ST77XX_MADCTL);
    write_data(0xC0);                   // bits 0-4 just keep 0 for default, bits 5-7 indicate inversion, like if your first pixel starts opposite side
                                                         // (MX, MY, MV = 0) (was 0x00 before but adafruit uses 0xC0)

    // Normal Display Mode ON
    write_command(ST77XX_NORON);
    sleep_ms(10);

    // Turn Display On
    write_command(ST77XX_DISPON);
    sleep_ms(100);

}

// void write_command(const st7735_pin_config_t *pins, uint8_t cmd) {
//     gpio_put(pins->rs_pin, 0);
//     gpio_put(pins->cs_pin, 0);
//     spi_write_blocking(pins->spi_port, &cmd, 1);
//     gpio_put(pins->cs_pin, 1);
// }


// void write_data(const st7735_pin_config_t *pins, uint8_t data) {
//     gpio_put(pins->rs_pin, 1);
//     gpio_put(pins->cs_pin, 0);
//     spi_write_blocking(pins->spi_port, &data, 1);
//     gpio_put(pins->cs_pin, 1);
// }

// void write_data_buffer(const st7735_pin_config_t *pins, const uint8_t *data, size_t len) {
//     gpio_put(pins->rs_pin, 1);
//     gpio_put(pins->cs_pin, 0);
//     spi_write_blocking(pins->spi_port, data, len);
//     gpio_put(pins->cs_pin, 1);
// }

// void fill_screen(uint16_t color) {
//     uint8_t upper = color >> 8;
//     uint8_t lower = color & 0xFF; 
//     uint8_t combined[2] = {upper, lower};
    
//     write_command(&interface_pins, ST77XX_CASET);
//     write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x00);   // X start 1 - offsetted
//     write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x7F);   // X end (160) - offsetted

//     write_command(&interface_pins, ST77XX_RASET);
//     write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x00);   // Y start 2 - offsetted
//     write_data(&interface_pins, 0x00); write_data(&interface_pins, 0x9F);   // Y end (129) - offsetted

//     write_command(&interface_pins, ST77XX_RAMWR);

//     for (int i = 0; i < 160 * 128; i++) {
//         write_data_buffer(&interface_pins, combined, 2);
//     }

// }


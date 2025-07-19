#include "hardware.h"


void st7735_spi_init() {
    gpio_init(SPI_ST7735_CS);
    gpio_set_dir(SPI_ST7735_CS, GPIO_OUT);
    gpio_put(SPI_ST7735_CS, 1);                 // Chip select is active-low, so keep high when unselected

    gpio_init(SPI_ST7735_RS);
    gpio_set_dir(SPI_ST7735_RS, GPIO_OUT);
    gpio_put(SPI_ST7735_RS, 0);

    gpio_init(SPI_ST7735_RST);
    gpio_set_dir(SPI_ST7735_RST, GPIO_OUT);
    gpio_put(SPI_ST7735_RST, 0);
}
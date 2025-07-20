#include "hardware.h"


void st7735_spi_init() {
    spi_init(spi0, 1000*1000);
    gpio_init(SPI_ST7735_CS);
    gpio_set_dir(SPI_ST7735_CS, GPIO_OUT);
    gpio_put(SPI_ST7735_CS, 1);                 // Chip select is active-low, so keep high when unselected

    gpio_init(SPI_ST7735_RS);
    gpio_set_dir(SPI_ST7735_RS, GPIO_OUT);
    gpio_put(SPI_ST7735_RS, 0);

    gpio_init(SPI_ST7735_RST);
    gpio_set_dir(SPI_ST7735_RST, GPIO_OUT);
    gpio_put(SPI_ST7735_RST, 0);

    gpio_init(SPI_ST7735_LEDA);
    gpio_set_dir(SPI_ST7735_LEDA, GPIO_OUT);
    gpio_put(SPI_ST7735_LEDA, 1);

    gpio_init(SPI_ST7735_SCK);
    gpio_set_function(SPI_ST7735_SCK, GPIO_FUNC_SPI);

    gpio_init(SPI_ST7735_MOSI);
    gpio_set_function(SPI_ST7735_MOSI, GPIO_FUNC_SPI);
}
#ifndef _HARDWARE_H
#define _HARDWARE_H


#include "pico/stdlib.h"
#include "hardware/spi.h"




// Pin are ports (defined in makefile typically?)


// SPI Port
#ifndef SPI_ST7735_PORT
    #define SPI_ST7735_PORT spi0
#endif

// Chip-Select Output Pin
#ifndef SPI_ST7735_CS
    #define SPI_ST7735_CS                   19
#endif

// ST7735 DC/RS Output Pin
#ifndef SPI_ST7735_RS
    #define SPI_ST7735_RS                   18
#endif

// Reset Output Pin
#ifndef SPI_ST7735_RST
    #define SPI_ST7735_RST                  17
#endif

#ifndef SPI_ST7735_LEDA
    #define SPI_ST7735_LEDA                 16
#endif

#ifndef SPI_ST7735_MOSI                                // unsure if needs to be defined
    #define SPI_ST7735_MOSI                 3
#endif

#ifndef SPI_ST7735_SCK                                 // unsure if needs to be defined
    #define SPI_ST7735_SCK                  2
#endif

static inline void tft_cs_low() {                       // Timing found at Pg25 (unsure about exact uses of NOP
    asm volatile("nop \n nop \n nop"); \
    gpio_put(SPI_ST7735_CS, 0);
    asm volatile("nop \n nop \n nop"); \
    asm volatile("nop \n nop \n nop"); \
}

static inline void tft_cs_high() {
    asm volatile("nop \n nop \n nop"); \
    gpio_put(SPI_ST7735_CS, 1);
    asm volatile("nop \n nop \n nop"); \
}

static inline void tft_rs_low() {
    asm volatile("nop \n nop \n nop"); \
    gpio_put(SPI_ST7735_RS, 0);
    asm volatile("nop \n nop \n nop"); \
}

static inline void tft_rs_high() {
    asm volatile("nop \n nop \n nop"); \
    gpio_put(SPI_ST7735_RS, 1);
    asm volatile("nop \n nop \n nop"); \
}

static inline void spi_write(uint8_t data) {
    spi_write_blocking(SPI_ST7735_PORT, &data, 1);
}

// Declarations / Prototyping
void st7735_spi_init();

#endif
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

#ifndef SPI_ST7735_MOSI                     3           // unsure if needs to be defined
    #define SPI_ST7735_MOSI
#endif

#ifndef SPI_ST7735_SCK                      2           // unsure if needs to be defined
    #define SPI_ST7735_SCK
#endif

// Declarations / Prototyping
void st7735_spi_init();

#endif
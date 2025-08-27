#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware.h"
#include "ST7735_TFT.h"
#include "fonts.h"


void draw_ascii_test(uint16_t color, uint16_t bg, uint8_t size) {
    int chars_per_row = 16;
    int x0 = 2, y0 = 2;

    for (char c = ' '; c <= '~'; c++) {
        int col = (c - ' ') % chars_per_row;
        int row = (c - ' ') / chars_per_row;
        int x = x0 + col * (5*size + 2); // 5 = char width, 2 = spacing
        int y = y0 + row * (7*size + 2); // 7 = char height, 2 = spacing

        draw_char(x, y, c, color, bg, size);
    }
}



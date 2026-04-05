#include "ST7735_TFT.h"
#include "ST7735_Screens.h"
#include "fonts.h"

// For Later:
/* 
typedef struct {
    void (*draw)(void);
} Screen_t;
*/

void draw_weather_screen() {
    draw_string(40, 10, "NWS", ST7735_BLUE, ST7735_WHITE, 3);
    draw_string(20, 40, "Nguyen Weather Service", ST7735_BLACK, ST7735_WHITE, 1);
    
    draw_string(40, 60, "67", ST7735_BLACK, ST7735_WHITE, 2);
    draw_bitmap(40, 80, ICON_WEATHER_CLOUD, ST7735_GRAY_MEDIUM, ST7735_WHITE, 3);

    draw_string(75, 60, "69", ST7735_BLACK, ST7735_WHITE, 2);
    draw_bitmap(75, 80, ICON_WEATHER_CLOUD, ST7735_GRAY_DARK, ST7735_WHITE, 3);

    draw_string(110, 60, "39", ST7735_BLACK, ST7735_WHITE, 2);
    draw_bitmap(110, 80, ICON_WEATHER_CLOUD, ST7735_BLACK, ST7735_WHITE, 3);
}

void draw_home_screen() {

}

void draw_spotify_screen() {

}
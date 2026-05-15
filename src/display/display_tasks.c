#include "drivers/ST7735_TFT.h"

void draw_screens_task (void *pvParameters) {
    // draw_weather_screen();
    // draw_rtc_screen();
    // draw_temp_screen();


}

void draw_weather_screen() {
    draw_string(55, 10, "NWS", ST7735_BLUE, ST7735_WHITE, 3);
    draw_string(25, 32, "Nguyen Weather Service", ST7735_BLACK, ST7735_WHITE, 1);
    
    draw_bitmap(75, 45, ICON_WEATHER_SUN, ST7735_YELLOW, ST7735_WHITE, 3);

    draw_bitmap(75, 70, ICON_WEATHER_SUN, ST7735_YELLOW, ST7735_WHITE, 3);

    draw_bitmap(75, 95, ICON_WEATHER_SUN, ST7735_YELLOW, ST7735_WHITE, 3);
}
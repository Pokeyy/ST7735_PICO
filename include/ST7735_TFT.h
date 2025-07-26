
// To Do List:
// Adapt for all screen tab types
// and insert adafruit commands for each one ig

#ifndef ST7735_TFT_H
#define ST7735_TFT_H

// ST7735 Defines Part1 (Red / Green Tab)
#define ST77XX_SWRESET              0x01


#define ST77XX_SLPOUT               0x11


#define ST7735_FRMCTR1              0xB1 // Frame Rate Control
#define ST7735_FRMCTR2              0xB2
#define ST7735_FRMCTR3              0xB3

#define ST7735_INVCTR               0xB4

#define ST7735_PWCTR1               0xC0
#define ST7735_PWCTR2               0xC1
#define ST7735_PWCTR3               0xC2
#define ST7735_PWCTR4               0xC3
#define ST7735_PWCTR5               0xC4

#define ST7735_VMCTR1               0xC5

#define ST77XX_INVOFF               0x20  
#define ST77XX_MADCTL               0x36

#define ST77XX_COLMOD               0x3A            // Define color format (12-bit/16-bit/18-bit/none)

// ST7735 Defines Part2 (Green Tab) (check back for resolutions or smth)
#define ST77XX_CASET                0x2A            // set address of each column (pixel column?)
#define ST77XX_RASET                0x2B            // set address of each row (pixel row?)
#define ST77XX_RAMWR                0x2C


//ST7735 Defines Part3 (Red / Green Tab)
#define ST7735_GMCTRP1              0xE0            // Gamma Polarity (+)
#define ST7735_GMCTRN1              0xE1            // Gamma Polarity (-)
#define ST77XX_NORON                0x13            // Normal Display Mode (On or Off)
#define ST77XX_DISPON               0x29            // Display On

// Color Code Definitions

#define ST7735_BLACK                0x0000
#define ST7735_WHITE                0xFFFF
#define ST7735_RED                  0xF800
#define ST7735_GREEN                0x07E0
#define ST7735_BLUE                 0x001F
#define ST7735_YELLOW               0xFFE0
#define ST7735_CYAN                 0x07FF
#define ST7735_MAGENTA              0xF81F

extern uint8_t disp_width, disp_height;

typedef struct {
    uint cs_pin;
    uint rs_pin;
    uint rst_pin;
    spi_inst_t *spi_port;
} st7735_pin_config_t;

/********************** FUNCTION PROTOTYPES ***************/

// For SPI:
void write_command(uint8_t cmd);
void write_data(uint8_t data);

//void write_data_buffer(const st7735_pin_config_t *pins, const uint8_t *data, size_t len);

// Functionality
void st7735_init_display();

void set_AddrArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void fill_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);

void fill_screen(uint16_t color);

void change_framerate();

void draw_shape();

void draw_line();

#if defined ST7735_GREEN_TAB
//
//
#endif

// RED_TAB


// BLACK_TAB 


// BLUE_TAB



#endif 

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

#define ST7735_BLACK                0x00
#define ST7735_WHITE                0xFF

typedef struct {
    cs_pin;
    rs_pin;
    rst_pin;
    spi_port;
} st7735_pin_config_t;

/********************** FUNCTION PROTOTYPES ***************/

// For SPI:
void write_command(const st7735_pin_config_t *pins, uint8_t cmd);
void write_data(const st7735_pin_config_t *pins, uint8_t data);

// Functionality
void fill_screen();

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
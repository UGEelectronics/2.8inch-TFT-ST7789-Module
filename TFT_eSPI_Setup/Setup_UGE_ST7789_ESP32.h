//******************************************************************************
// Setup_UGE_ST7789_ESP32.h
// UGE Electronics — 2.8" TFT 240x320 ST7789 (SPI)
//
// Install:
//   1. Copy this file to:
//        Documents/Arduino/libraries/TFT_eSPI/User_Setups/
//   2. In User_Setup_Select.h comment out other setups and add:
//        #include <User_Setups/Setup_UGE_ST7789_ESP32.h>
//
// Module header (silk): GND VCC CLK MOSI RES DC BLK MISO
// CS is not exposed — keep TFT_CS as -1.
//******************************************************************************

#define USER_SETUP_ID 7789

#define ST7789_DRIVER

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// Colour — confirmed for this module; change only if ColorTest fails
#define TFT_RGB_ORDER TFT_RGB
//#define TFT_RGB_ORDER TFT_BGR

//#define TFT_INVERSION_ON
#define TFT_INVERSION_OFF

// ---- ESP32 recommended wiring (edit if you use other GPIOs) ----
#define TFT_MISO -1     // optional; module MISO often unused
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   -1     // no CS pin on this module
#define TFT_DC   12
#define TFT_RST  13

// Optional: drive backlight from a GPIO instead of tying BLK to 3.3V
// #define TFT_BL   15
// #define TFT_BACKLIGHT_ON HIGH

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

#define SPI_FREQUENCY        40000000
#define SPI_READ_FREQUENCY   20000000
#define SPI_TOUCH_FREQUENCY  2500000

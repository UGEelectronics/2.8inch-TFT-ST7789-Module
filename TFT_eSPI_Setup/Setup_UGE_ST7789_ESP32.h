//******************************************************************************
// Setup_UGE_ST7789_ESP32.h
// UGE Electronics — 2.8" TFT 240x320 ST7789 (SPI), 7-pin module
//
// Pins (silk): GND, 3V3, CS, RST, SCK, MOSI, D/C
// Backlight is hardwired to 3.3V on the PCB (no BLK pin / no software control).
// Shop: https://uge-one.com/product/st7789-2-8-inch-spi-lcd-tft-320x240-module-3-3v/
//
// Install:
//   1. Copy this file to:
//        Documents/Arduino/libraries/TFT_eSPI/User_Setups/
//   2. In User_Setup_Select.h comment out other setups and add:
//        #include <User_Setups/Setup_UGE_ST7789_ESP32.h>
//******************************************************************************

#define USER_SETUP_ID 7789

#define ST7789_DRIVER

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define TFT_RGB_ORDER TFT_RGB
//#define TFT_RGB_ORDER TFT_BGR

//#define TFT_INVERSION_ON
#define TFT_INVERSION_OFF

// ---- ESP32 recommended wiring (edit if you use other GPIOs) ----
#define TFT_MISO -1     // MISO not on this module
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    2
#define TFT_DC   12
#define TFT_RST  13

// No TFT_BL — backlight is permanently powered on the module

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

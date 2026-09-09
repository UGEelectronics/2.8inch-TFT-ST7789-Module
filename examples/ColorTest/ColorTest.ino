/*******************************************************************************
 * ColorTest — UGE 2.8" ST7789 240x320
 *
 * Requires TFT_eSPI configured with Setup_UGE_ST7789_ESP32.h
 * (see docs/USER_GUIDE.md in this repository).
 *
 * BOOT button (GPIO 0) advances screens; otherwise ~8 s per screen.
 ******************************************************************************/

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define BTN_PIN  0

static bool btnPressed(void)
{
  return digitalRead(BTN_PIN) == LOW;
}

static void waitNext(void)
{
  for (int i = 0; i < 80; i++)
  {
    if (btnPressed())
    {
      while (btnPressed())
        delay(20);
      delay(150);
      return;
    }
    delay(100);
  }
}

static void drawRaw565(void)
{
  const int top = 40;
  const int w = tft.width();
  const int h = tft.height();
  const int bh = (h - top) / 3;

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(4, 4);
  tft.println("TEST 1: RAW 565");
  tft.setTextSize(1);
  tft.println("Top RED / Mid GREEN / Bot BLUE");

  tft.fillRect(0, top, w, bh, 0xF800);
  tft.fillRect(0, top + bh, w, bh, 0x07E0);
  tft.fillRect(0, top + 2 * bh, w, h - top - 2 * bh, 0x001F);

  tft.setTextColor(TFT_WHITE);
  tft.setCursor(8, top + 8);
  tft.print("RED 0xF800");
  tft.setCursor(8, top + bh + 8);
  tft.print("GREEN 0x07E0");
  tft.setCursor(8, top + 2 * bh + 8);
  tft.print("BLUE 0x001F");
}

static void drawNamed(void)
{
  const int w = tft.width();
  const int h = tft.height();
  const int hw = w / 2;
  const int hh = (h - 36) / 2;

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(4, 4);
  tft.println("TEST 2: NAMES");
  tft.setTextSize(1);
  tft.println("TFT_RED / GREEN / BLUE / WHITE");

  tft.fillRect(0, 36, hw, hh, TFT_RED);
  tft.fillRect(hw, 36, w - hw, hh, TFT_GREEN);
  tft.fillRect(0, 36 + hh, hw, h - 36 - hh, TFT_BLUE);
  tft.fillRect(hw, 36 + hh, w - hw, h - 36 - hh, TFT_WHITE);

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(12, 36 + hh / 2 - 8);
  tft.print("RED");
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(hw + 12, 36 + hh / 2 - 8);
  tft.print("GREEN");
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(12, 36 + hh + hh / 2 - 8);
  tft.print("BLUE");
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(hw + 12, 36 + hh + hh / 2 - 8);
  tft.print("WHITE");
}

static void drawColor565(void)
{
  const int w = tft.width();
  const int h = tft.height();
  const int bh = (h - 40) / 3;
  const uint16_t cR = tft.color565(255, 0, 0);
  const uint16_t cG = tft.color565(0, 255, 0);
  const uint16_t cB = tft.color565(0, 0, 255);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(4, 4);
  tft.println("TEST 3: color565");
  tft.setTextSize(1);
  tft.println("Same API as your applications");

  tft.fillRect(0, 40, w, bh, cR);
  tft.fillRect(0, 40 + bh, w, bh, cG);
  tft.fillRect(0, 40 + 2 * bh, w, bh, cB);

  tft.setTextColor(TFT_WHITE);
  tft.setCursor(8, 48);
  tft.printf("R = 0x%04X", cR);
  tft.setCursor(8, 48 + bh);
  tft.printf("G = 0x%04X", cG);
  tft.setCursor(8, 48 + 2 * bh);
  tft.printf("B = 0x%04X", cB);
}

static void drawNatural(void)
{
  const int w = tft.width();
  const int h = tft.height();

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(4, 4);
  tft.println("TEST 4: NATURAL");
  tft.setTextSize(1);
  tft.println("Skin / Sky / Grass");

  tft.fillRect(0, 40, w / 3, h - 40, tft.color565(255, 180, 140));
  tft.fillRect(w / 3, 40, w / 3, h - 40, tft.color565(100, 180, 255));
  tft.fillRect(2 * (w / 3), 40, w - 2 * (w / 3), h - 40, tft.color565(40, 160, 60));

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(8, h / 2);
  tft.print("SKIN");
  tft.setCursor(w / 3 + 8, h / 2);
  tft.print("SKY");
  tft.setCursor(2 * (w / 3) + 8, h / 2);
  tft.print("GRASS");
}

static void drawPass(void)
{
  tft.fillScreen(TFT_DARKGREEN);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
  tft.setTextSize(2);
  tft.setCursor(40, tft.height() / 2 - 20);
  tft.println("LCD OK");
  tft.setTextSize(1);
  tft.setCursor(16, tft.height() / 2 + 12);
  tft.println("UGE 2.8\" ST7789 ready");
  tft.setCursor(16, tft.height() / 2 + 28);
  tft.println("Try TFT_eSPI examples next");
}

void setup()
{
  Serial.begin(115200);
  delay(300);
  pinMode(BTN_PIN, INPUT_PULLUP);

  Serial.println();
  Serial.println("UGE 2.8\" ST7789 ColorTest (7-pin)");
  Serial.println("Setup: Setup_UGE_ST7789_ESP32.h via User_Setup_Select.h");
  Serial.println("Wire: CS=2 DC=12 RST=13 MOSI=23 SCK=18 | BL hardwired");

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, tft.height() / 2 - 16);
  tft.println("UGE LCD TEST");
  tft.setTextSize(1);
  tft.setCursor(16, tft.height() / 2 + 16);
  tft.println("BOOT=next | auto ~8s");
  delay(1500);
}

void loop()
{
  drawRaw565();
  waitNext();
  drawNamed();
  waitNext();
  drawColor565();
  waitNext();
  drawNatural();
  waitNext();
  drawPass();
  waitNext();
}

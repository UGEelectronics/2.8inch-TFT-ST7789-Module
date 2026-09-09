# 2.8″ TFT LCD Module (ST7789) — 240×320

![UGE 2.8" ST7789 TFT module](images/module.jpg)

SPI colour display module for Arduino / ESP32 and similar boards.  
**Controller:** ST7789 · **Resolution:** 240 × 320 RGB · **Interface:** 4-wire SPI

Repository: [UGEelectronics/2.8inch-TFT-ST7789-Module](https://github.com/UGEelectronics/2.8inch-TFT-ST7789-Module)

---

## Product description

This is a compact **2.8-inch TFT** panel on a blue breakout PCB with an 8-pin header. It is intended for DIY electronics, IoT dashboards, meters, and handheld UIs.

| Item | Specification |
|------|----------------|
| Size | 2.8 inch diagonal |
| Resolution | **240 × 320** pixels |
| Colour | RGB, 16-bit (RGB565) |
| Driver IC | **ST7789** |
| Bus | SPI (CLK, MOSI; MISO optional) |
| Logic / supply | **3.3 V** (do not use 5 V logic without a level shifter) |
| Backlight | `BLK` pin (tie to 3.3 V for always-on, or drive from a GPIO) |
| Chip select | **Not brought out** — CS is hard-wired on the PCB (always selected) |

### Header pinout (silk screen)

Pins from the top of the header (next to the glass corner) downward:

| # | Label | Function |
|---|--------|----------|
| 1 | **GND** | Ground |
| 2 | **VCC** | 3.3 V power |
| 3 | **CLK** | SPI clock (SCK) |
| 4 | **MOSI** | SPI data (MCU → LCD) |
| 5 | **RES** | Reset |
| 6 | **DC** | Data / Command |
| 7 | **BLK** | Backlight enable |
| 8 | **MISO** | SPI data (LCD → MCU) — optional; leave unconnected for write-only use |

> There is **no CS pin** on this module. In TFT_eSPI set `#define TFT_CS -1`.

---

## Quick start (ESP32 + TFT_eSPI)

1. Install **Arduino IDE** and the **ESP32** board package (Espressif).
2. Library Manager → install **TFT_eSPI** by Bodmer.
3. Copy this repo’s setup file into the library setups folder (see [User guide](docs/USER_GUIDE.md)).
4. Select that setup in `User_Setup_Select.h`.
5. Wire the module (table below), open `examples/ColorTest`, and Upload.

### Recommended ESP32 wiring

| Module pin | ESP32 GPIO |
|------------|------------|
| GND | GND |
| VCC | **3.3 V** |
| CLK | **18** |
| MOSI | **23** |
| RES | **13** |
| DC | **12** |
| BLK | **3.3 V** (or any free GPIO) |
| MISO | leave open (or **19** if you need reads) |

These GPIOs match `TFT_eSPI_Setup/Setup_UGE_ST7789_ESP32.h`.

---

## Repository contents

| Path | Description |
|------|-------------|
| [`docs/USER_GUIDE.md`](docs/USER_GUIDE.md) | Full install, wiring, troubleshooting |
| [`TFT_eSPI_Setup/Setup_UGE_ST7789_ESP32.h`](TFT_eSPI_Setup/Setup_UGE_ST7789_ESP32.h) | Pin/driver file for TFT_eSPI |
| [`examples/ColorTest/`](examples/ColorTest/) | RGB colour test sketch |
| [`images/module.jpg`](images/module.jpg) | Product photo |

---

## Why configure `User_Setup_Select.h`?

TFT_eSPI’s **built-in examples** (graphs, fonts, sprites, …) only include `<TFT_eSPI.h>`.  
They read pins from the library setup — **not** from a sketch-local header.

Configuring **one** setup file in the library means:

- Your product colour test works
- Every TFT_eSPI example works with the same wiring
- The user’s own sketches need only `#include <TFT_eSPI.h>`

Step-by-step: [docs/USER_GUIDE.md](docs/USER_GUIDE.md)

---

## Licence

MIT — see [LICENSE](LICENSE).

© UGE Electronics

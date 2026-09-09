# User guide — 2.8″ ST7789 TFT (UGE)

Library install, ESP32 wiring, TFT_eSPI setup, and the colour test.

## 1. Hardware checklist

- ESP32 development board (3.3 V I/O)
- UGE 2.8″ ST7789 module (**7 pins**)
- Dupont wires / breadboard
- Power: module **3.3V** pin from ESP32 **3.3 V**

**Do not** use 5 V on the logic or power pins.

### Module pins (silk)

| Pin | Meaning |
|-----|---------|
| GND | Ground |
| 3V3 | Power (3.3 V) |
| CS | Chip select |
| RST | Reset |
| SCK | SPI clock |
| MOSI | SPI data out |
| D/C | Data / Command |

**Backlight:** permanently powered from 3.3 V through a small resistor on the PCB. There is **no BLK pin** and the user **cannot** dim or switch the backlight in software.

**MISO:** not brought out — write-only SPI is enough for normal graphics.

## 2. Install Arduino tools

1. Install [Arduino IDE](https://www.arduino.cc/en/software) (2.x recommended).
2. **Tools → Board → Boards Manager** → search **esp32** → install **esp32 by Espressif Systems**.
3. Select your board (e.g. **ESP32 Dev Module**) and COM port.

## 3. Install TFT_eSPI

1. **Sketch → Include Library → Manage Libraries**
2. Search **TFT_eSPI**
3. Install **TFT_eSPI** by **Bodmer**

## 4. Configure TFT_eSPI (required once)

Configuring the library once makes **all** sketches and **built-in examples** use this module’s wiring.

### 4.1 Copy the setup file

Copy from this repository:

```text
TFT_eSPI_Setup/Setup_UGE_ST7789_ESP32.h
```

to:

```text
Documents/Arduino/libraries/TFT_eSPI/User_Setups/Setup_UGE_ST7789_ESP32.h
```

### 4.2 Edit `User_Setup_Select.h`

Open:

```text
Documents/Arduino/libraries/TFT_eSPI/User_Setup_Select.h
```

1. **Comment out** the default setup (often `#include <User_Setup.h>`).
2. **Add:**

```cpp
#include <User_Setups/Setup_UGE_ST7789_ESP32.h>
```

Save. Only **one** setup `#include` may be active.

### 4.3 Defaults in the setup file

| Setting | Value |
|---------|--------|
| Driver | `ST7789_DRIVER` |
| Size | 240 × 320 |
| `TFT_CS` | GPIO **2** |
| `TFT_DC` | GPIO **12** |
| `TFT_RST` | GPIO **13** |
| `TFT_MOSI` | GPIO **23** |
| `TFT_SCLK` | GPIO **18** |
| Colour order | `TFT_RGB` |
| Inversion | `TFT_INVERSION_OFF` |

To use other GPIOs, edit **only** `Setup_UGE_ST7789_ESP32.h`.

## 5. Wire ESP32 ↔ module

| Module | ESP32 |
|--------|--------|
| GND | GND |
| 3V3 | 3.3 V |
| CS | 2 |
| RST | 13 |
| SCK | 18 |
| MOSI | 23 |
| D/C | 12 |

## 6. Run the colour test

1. Open `examples/ColorTest/ColorTest.ino`.
2. Upload.
3. Expect red / green / blue / white / natural-colour screens.

- **BOOT** (GPIO 0) advances screens, or wait ~8 s.

If colours are wrong, see troubleshooting — then edit the setup file and re-upload.

## 7. Use TFT_eSPI built-in examples

After step 4:

```text
File → Examples → TFT_eSPI → …
```

No extra pin definitions are required in those examples.

## 8. Minimal application sketch

```cpp
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Hello UGE TFT", 10, 20, 2);
}

void loop() {}
```

## 9. Troubleshooting

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Black screen | Power / wiring | Check 3.3 V, CS, DC, RST, SCK, MOSI |
| White screen | Wrong SPI pins or setup not selected | Re-check `User_Setup_Select.h` and wiring |
| Red ↔ blue swapped | RGB order | `#define TFT_RGB_ORDER TFT_BGR` |
| Negative / inverted | Panel inversion | `TFT_INVERSION_ON`, comment out `TFT_INVERSION_OFF` |
| Examples use wrong pins | Old setup still active | Only one `#include` in `User_Setup_Select.h` |
| Want backlight off | Not possible on this module | Backlight is hardwired to 3.3 V |

## 10. Changing pins later

Edit `Setup_UGE_ST7789_ESP32.h`, save, recompile and upload. Sketches do not need pin changes.

---

[GitHub — UGEelectronics/2.8inch-TFT-ST7789-Module](https://github.com/UGEelectronics/2.8inch-TFT-ST7789-Module)  
[Buy this module](https://uge-one.com/product/st7789-2-8-inch-spi-lcd-tft-320x240-module-3-3v/)

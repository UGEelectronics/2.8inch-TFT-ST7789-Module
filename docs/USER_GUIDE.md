# User guide — 2.8″ ST7789 TFT (UGE)

This guide covers library install, ESP32 wiring, TFT_eSPI setup, and the colour test.

## 1. Hardware checklist

- ESP32 development board (3.3 V I/O)
- This 2.8″ ST7789 module
- Dupont wires / breadboard
- Power: module **VCC = 3.3 V** (same as ESP32 3.3 V rail)

**Do not** power the logic pins from 5 V.

### Module pins (as printed on the PCB)

`GND · VCC · CLK · MOSI · RES · DC · BLK · MISO`

- **CS is not on the connector** — leave `TFT_CS` as `-1` in software.
- **BLK** must be high for a visible image (connect to 3.3 V, or to a GPIO set HIGH).
- **MISO** is unused for normal drawing; you can leave it disconnected.

## 2. Install Arduino tools

1. Install [Arduino IDE](https://www.arduino.cc/en/software) (2.x recommended).
2. **File → Preferences → Additional boards manager URLs** — add Espressif’s URL if needed, then  
   **Tools → Board → Boards Manager** → search **esp32** → install **esp32 by Espressif Systems**.
3. Select your board, e.g. **ESP32 Dev Module**, and the correct COM port.

## 3. Install TFT_eSPI (fresh library)

1. **Sketch → Include Library → Manage Libraries**
2. Search **TFT_eSPI**
3. Install **TFT_eSPI** by **Bodmer**

You do **not** need Adafruit_GFX separately for this library.

## 4. Configure TFT_eSPI for this module (required once)

TFT_eSPI stores pins in the **library** folder so **all** sketches and examples share the same wiring.

### 4.1 Copy the setup file

From this repository, copy:

```text
TFT_eSPI_Setup/Setup_UGE_ST7789_ESP32.h
```

to your Arduino libraries folder, for example:

```text
Documents/Arduino/libraries/TFT_eSPI/User_Setups/Setup_UGE_ST7789_ESP32.h
```

(Exact path depends on your OS / Arduino install.)

### 4.2 Select it in `User_Setup_Select.h`

Open:

```text
Documents/Arduino/libraries/TFT_eSPI/User_Setup_Select.h
```

1. **Comment out** the default setup line (often `#include <User_Setup.h>`).
2. **Add** (or uncomment) this line:

```cpp
#include <User_Setups/Setup_UGE_ST7789_ESP32.h>
```

Save the file.

Only **one** setup `#include` may be active.

### 4.3 What the setup defines

| Setting | Value |
|---------|--------|
| Driver | `ST7789_DRIVER` |
| Size | 240 × 320 |
| `TFT_CS` | `-1` (no CS pin on module) |
| `TFT_DC` | GPIO **12** |
| `TFT_RST` | GPIO **13** |
| `TFT_MOSI` | GPIO **23** |
| `TFT_SCLK` | GPIO **18** |
| Colour order | `TFT_RGB` |
| Inversion | `TFT_INVERSION_OFF` |

If you wire DC / RST / MOSI / SCK differently, edit **only** `Setup_UGE_ST7789_ESP32.h` (not every sketch).

## 5. Wire ESP32 ↔ module

| Module | ESP32 |
|--------|--------|
| GND | GND |
| VCC | 3.3 V |
| CLK | 18 |
| MOSI | 23 |
| RES | 13 |
| DC | 12 |
| BLK | 3.3 V |
| MISO | — (optional) |

## 6. Run the colour test

1. Open `examples/ColorTest/ColorTest.ino` from this repository.
2. Select board + port → **Upload**.
3. You should see labelled red / green / blue / white / natural-colour screens.

- Press **BOOT** (GPIO 0 on many ESP32 boards) to advance.
- Or wait ~8 seconds per screen.

If colours look wrong (red↔blue, or “negative” image), see troubleshooting below — then edit `Setup_UGE_ST7789_ESP32.h` and re-upload.

## 7. Use TFT_eSPI built-in examples

After step 4 is done, open any example under:

```text
File → Examples → TFT_eSPI → …
```

No extra pin code is required. The library uses your User Setup automatically.

## 8. Start your own application

Minimal sketch:

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
| Completely black | No power / BLK low / wrong pins | Check 3.3 V, tie **BLK** to 3.3 V, verify DC/RST/CLK/MOSI |
| White screen | Init / wiring / SPI pins | Confirm setup matches physical wires; re-check `User_Setup_Select.h` |
| Wrong colours (R↔B) | RGB order | In setup: `#define TFT_RGB_ORDER TFT_BGR` |
| Inverted / negative | Panel inversion | Use `TFT_INVERSION_ON`, comment out `TFT_INVERSION_OFF` |
| Examples still use old pins | Wrong setup selected | Ensure only **one** `#include` in `User_Setup_Select.h` |
| Compile errors about setup | Path / include name | File must be under `TFT_eSPI/User_Setups/` and included with that path |

## 10. Changing pins later

Edit `Setup_UGE_ST7789_ESP32.h`, save, then **recompile and upload**.  
You do not need to change each sketch.

---

Support / product: [UGE Electronics — GitHub repo](https://github.com/UGEelectronics/2.8inch-TFT-ST7789-Module)

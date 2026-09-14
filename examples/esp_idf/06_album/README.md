# 06_album

[English](README.md) | [中文](README_CN.md)

Photo album: load `jpg` / `jpeg` / `png` / `bmp` from the SD card and show them full-screen.

BSP: [viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a). First-time setup: [../README.md](../README.md).

---

## Prepare pictures

1. Format the Micro SD as **FAT32**
2. Put images in an **`album` folder** (recommended) or in the card root
3. Sizes close to the panel (800×480 or 480×272) run smoother; JPEG uses less RAM
4. Insert the card before power-on

Controls: tap the **left** half for previous, **right** half or the **BOOT** button for next. Auto-advance defaults to every 5 seconds.

---

## First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Install **ESP-IDF** (Espressif)
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**, IDF **≥ 5.5**
4. Status bar shows `v5.5.x`

---

## Steps

1. **File → Open Folder** → only `06_album`
2. USB in; target **esp32s3**; select the serial port
3. For 480×272: menuconfig → **Component config → Board Support Package → Display → 4.3" LCD panel** → `UEDX48270043 480x272`
4. Slideshow interval: menuconfig → **Example Configuration** (default 5000 ms, `0` = off)
5. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

Build OK: `Project build complete`, no `FAILED`.

---

## How you know it worked

**On the screen:** a photo, caption `1 / N  filename`; tap or BOOT changes the picture.

**On the serial log:**

```
I (xxx) album: electronic album
I (xxx) BSP: SD card mounted at /sdcard
I (xxx) album: scanned /sdcard/album -> 8 image(s)
I (xxx) BSP: RGB LCD initialized
I (xxx) album: 8 image(s), tap left/right or BOOT
I (xxx) album: show [1/8] S:album/photo1.jpg
```

The number `8` depends on how many files you copied.

- **OK:** `SD card mounted`, `scanned ... -> N image(s)` with N>0, `show [1/N]`, picture on the LCD
- **Fail:** `SD mount failed` — card, FAT32, seating  
  On-screen `No images` or N=0 — use jpg/jpeg/png/bmp in `/album` or the root  
  Garbled LCD — select the 480×272 panel option if that is your module

---

## 480×272 panel

Same as `05_display_lvgl_port`: pick **UEDX48270043 480x272** in menuconfig, or uncomment `CONFIG_BSP_LCD_PANEL_480X272=y` in this folder’s `sdkconfig.defaults`. Delete an existing `sdkconfig` before rebuilding.

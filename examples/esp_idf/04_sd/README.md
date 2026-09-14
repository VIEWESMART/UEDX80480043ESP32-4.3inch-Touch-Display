# 04_sd

[English](README.md) | [中文](README_CN.md)

Mounts a Micro SD card at `/sdcard`, lists files, then writes and reads `bsp_sd_test.txt`.

BSP: [viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a). First-time setup: [../README.md](../README.md).

---

## What you need

- Board + USB cable
- Micro SD formatted **FAT32** (insert before power-on if you can)
- VS Code and ESP-IDF **≥ 5.5** via EIM

SPI pins: MOSI=11, MISO=13, SCLK=12, CS=10.

### First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Install **ESP-IDF** (Espressif)
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**, IDF **≥ 5.5**
4. Status bar shows `v5.5.x`

---

## Steps

1. Format the card FAT32 and insert it
2. **File → Open Folder** → only `04_sd`
3. USB in; target **esp32s3**; select the serial port
4. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

Build OK: `Project build complete`, no `FAILED`.

---

## How you know it worked

```
I (xxx) sd: SD SPI example  MOSI=11 MISO=13 SCLK=12 CS=10
I (xxx) BSP: SD card mounted at /sdcard
I (xxx) sd: listing /sdcard
I (xxx) sd:   ...
I (xxx) sd: wrote /sdcard/bsp_sd_test.txt
I (xxx) sd: read back: UEDX80480043 SD test OK
I (xxx) sd: SD test done
```

- **OK:** `SD card mounted`, `wrote`, `read back: UEDX80480043 SD test OK`, `SD test done`
- **Fail:** `mount failed` — reseat the card, use FAT32 (exFAT often fails)

On a PC you should see `bsp_sd_test.txt` containing `UEDX80480043 SD test OK`.

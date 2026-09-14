# 05_display_lvgl_port

[English](README.md) | [中文](README_CN.md)

Brings up the 4.3" RGB LCD with `bsp_display_start()` and `esp_lvgl_adapter`, then runs the **LVGL Widgets** demo. Touch is GT911.

BSP: [viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a). First-time setup: [../README.md](../README.md).

Default panel is **800×480**. For 480×272 see the end of this page.

---

## First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Install **ESP-IDF** (Espressif)
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**
4. Pick **IDF 5.5 or newer** (PSRAM is already enabled in this example’s defaults)
5. Status bar shows `v5.5.x`

---

## Steps

1. **File → Open Folder** → only `05_display_lvgl_port`
2. USB in; target **esp32s3**; select the serial port
3. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

The first build downloads the BSP, LVGL and `esp_lvgl_adapter`. Success: `Project build complete`, no `FAILED`.

---

## How you know it worked

**On the screen:** backlight on, colorful widgets (buttons, sliders, charts), touch responds.

**On the serial log:**

```
I (xxx) lvgl_port: display + LVGL via esp_lvgl_adapter  800x480
I (xxx) BSP: Initializing RGB LCD UEDX80480043: 800x480 RGB565, ...
I (xxx) BSP: RGB LCD initialized
I (xxx) BSP: GT911 found at 0x5D
I (xxx) BSP: GT911 touch initialized
I (xxx) BSP: Display registered to esp_lvgl_adapter: 800x480
I (xxx) lvgl_port: LVGL widgets running, touch GT911 to interact
```

- **OK:** `RGB LCD initialized`, `Display registered`, `LVGL widgets running`; UI on screen and touch works  
  (GT911 may also be `0x14`)
- **Fail:** `bsp_display_start failed` — USB, IDF ≥ 5.5, target esp32s3  
  Tear / drift — keep the example PSRAM defaults; 480×272 needs the panel option  
  Picture but no touch — run `01_i2c_scan` first

---

## 480×272 panel

F1 → **ESP-IDF: SDK Configuration Editor (menuconfig)** → **Component config → Board Support Package → Display → 4.3" LCD panel** → `UEDX48270043 480x272` → save, rebuild, flash.

You can also uncomment `CONFIG_BSP_LCD_PANEL_480X272=y` in this folder’s `sdkconfig.defaults`. If `sdkconfig` already exists, delete it so the new defaults apply.

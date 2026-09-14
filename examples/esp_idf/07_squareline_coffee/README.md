# 07_squareline_coffee

[English](README.md) | [中文](README_CN.md)

SquareLine Studio coffee-machine UI on UEDX80480043E-WB. The LCD and GT911 come from **[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)**.

The UI is designed for **800×480**. First-time setup: [../README.md](../README.md).

---

## First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Install **ESP-IDF** (Espressif)
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**
4. Pick **IDF 5.5 or newer**
5. Status bar shows `v5.5.x`

---

## Steps

1. **File → Open Folder** → only `07_squareline_coffee`
2. If you built this example with a local BSP or an older tree, delete `build`, `managed_components` and `sdkconfig` first
3. USB in; target **esp32s3**; select the serial port
4. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

This UI has many images; the first build downloads the BSP and takes longer. Success: `Project build complete`, no `FAILED`.

---

## How you know it worked

**On the screen:** backlight on, coffee splash / home screen, buttons and sliders respond to touch.

**On the serial log:**

```
I (xxx) coffee: SquareLine coffee UI  800x480
I (xxx) BSP: RGB LCD initialized
I (xxx) BSP: GT911 found at 0x5D
I (xxx) BSP: Display registered to esp_lvgl_adapter: 800x480
I (xxx) coffee: SquareLine UI running, touch GT911 to interact
```

- **OK:** `RGB LCD initialized` and `SquareLine UI running`, coffee UI on the LCD
- **Fail:** `bsp_display_start failed` — IDF ≥ 5.5, target esp32s3  
  Missing `ui_init` at link time — keep `main/ui/filelist.txt`  
  Garbled layout — this project is 800×480; do not run it on 480×272 as-is

---

## Panel note

The SquareLine project is 800×480. A 480×272 module will not match even if you change the BSP panel option.

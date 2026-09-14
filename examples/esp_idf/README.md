# VIEWE 4.3" examples (first-time guide)

[English](README.md) | [中文](README_CN.md)

Every example pulls the BSP from the Espressif Component Registry. You do **not** need a local copy of the BSP sources next to the examples:

[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a) `^1.0.0`

On the first build, VS Code / IDF downloads the BSP into that example’s `managed_components/` folder. Each example is self-contained (board Flash / PSRAM settings live in that folder’s `sdkconfig.defaults`) and must not point at other local paths in this repo.

| Folder | What it does | Success looks like |
| --- | --- | --- |
| [01_i2c_scan](01_i2c_scan/README.md) | Scan the touch I2C bus | Serial shows `0x5D` or `0x14` |
| [02_wifi](02_wifi/README.md) | Join a 2.4 GHz Wi-Fi AP | Serial shows `Wi-Fi got IP` |
| [03_ble](03_ble/README.md) | Phone BLE pairing | Phone finds `UEDX-4.3-S3` and pairs |
| [04_sd](04_sd/README.md) | Read/write Micro SD | Serial shows `SD test done` |
| [05_display_lvgl_port](05_display_lvgl_port/README.md) | LCD + touch | Widgets on screen, touch works |
| [06_album](06_album/README.md) | Photo album from SD | Pictures on the LCD |
| [07_squareline_coffee](07_squareline_coffee/README.md) | SquareLine coffee UI | Coffee machine UI, touch works |
| [08_gui_guider_monitoring](08_gui_guider_monitoring/README.md) | GUI Guider monitor UI | Dashboard on screen, touch works |

Each example folder has its own English/Chinese README. You can open just that folder and follow it. The software install below is the same for all examples.

---

## What you need

1. Board: UEDX80480043E-WB (800×480) or the same PCB with UEDX48270043 (480×272)
2. USB Type-C cable that carries data (not charge-only)
3. A PC (Windows steps below; Mac / Linux button names are similar)
4. Internet (first time downloads IDF tools and the BSP)

---

## First time: install ESP-IDF with EIM, then use VS Code

### 1. Install VS Code

Download from [https://code.visualstudio.com/](https://code.visualstudio.com/) and install with the defaults.

### 2. Install the ESP-IDF extension

1. Open VS Code
2. Click **Extensions** (four squares) on the left
3. Search `ESP-IDF`
4. Install the one published by **Espressif**

### 3. Install ESP-IDF with EIM (do not unzip IDF by hand)

EIM is the Espressif Installation Manager. After the extension is installed, use it to get the compiler, Python, and IDF sources.

1. Press **F1** (or `Ctrl+Shift+P`) to open the Command Palette
2. Run **ESP-IDF: Open ESP-IDF Installation Manager**
3. In the EIM window choose **Easy Installation**
4. Click **Start Installation**
5. Pick **ESP-IDF 5.5 or newer** (this BSP needs `idf >= 5.5`), for example 5.5.4
6. For the download mirror: Espressif’s server is often faster in China; otherwise GitHub
7. Wait for the progress bar (can take from minutes to an hour)
8. Click **Go to Dashboard**. Your version (e.g. `v5.5.4`) should be listed as installed
9. Close EIM. Restart VS Code if the status bar does not show the IDF version

How you know IDF is ready:

- The EIM dashboard lists that version as installed / ready
- The **bottom status bar** in VS Code shows an ESP-IDF version such as `v5.5.4`, not “IDF is not configured”

### 4. Open one example folder (not the parent `esp_idf` folder)

Each of `01_i2c_scan`, `02_wifi`, … is its **own** project.

1. **File → Open Folder**
2. Select only one example, e.g. `...\examples\esp_idf\01_i2c_scan`
3. Trust the folder if VS Code asks

If you opened the parent `examples` or `examples/esp_idf` directory, the build will fail. Close the window and open a single example folder.

### 5. Set the chip and serial port

1. Plug USB-C into the board and power it
2. F1 → **ESP-IDF: Set Espressif Device Target** → **esp32s3**
3. F1 → **ESP-IDF: Select Port to Use** → pick the board’s COM / tty port  
   On Windows, check Device Manager → Ports (USB JTAG / USB Serial is typical)

The status bar should look like: `v5.5.x` · `esp32s3` · `COM3` (the number varies).

### 6. Build, flash, watch the log

| Action | Command Palette |
| --- | --- |
| Build only | **ESP-IDF: Build your Project** |
| Flash | **ESP-IDF: Flash your Project** |
| Serial monitor | **ESP-IDF: Monitor Device** (`Ctrl+E` then `M`) |
| All three | **ESP-IDF: Build, Flash and Start a Monitor on Your Device** (`Ctrl+E` then `D`) |

You can also use the **bottom status bar**: hammer (build), lightning (flash), plug (monitor).

The first build downloads the BSP and other components. A good build ends with something like:

```
Project build complete. To flash, run:
idf.py -p COMx flash
```

or `Creating esp32s3 image...` and no red `FAILED`.

Keep USB connected while flashing. If it stalls, hold **BOOT** and retry, or unplug/replug USB.

The monitor uses **115200** baud. Leave the monitor with `Ctrl+]`.

### 7. If you built these examples with a local BSP before

Delete that example’s `build`, `managed_components` and `sdkconfig` folders/files, then build again so IDF fetches `viewesmart/bsp_uedx80480043_wb_a` from the registry and regenerates board settings from this folder’s `sdkconfig.defaults`.

---

## Switch the LCD (480×272)

The default is **800×480**. For UEDX48270043 (480×272):

1. F1 → **ESP-IDF: SDK Configuration Editor (menuconfig)**
2. **Component config → Board Support Package → Display → 4.3" LCD panel**
3. Choose `UEDX48270043 480x272`
4. Save, then build and flash again

You can also uncomment `CONFIG_BSP_LCD_PANEL_480X272=y` in that example’s own `sdkconfig.defaults`. If `sdkconfig` already exists, delete it first. Do not run `07` / `08` on 480×272 — those UIs are 800×480.

---

## Common problems

| Symptom | What to try |
| --- | --- |
| Extension says IDF is not configured | Run EIM again, then restart VS Code |
| No COM port | Use a data-capable USB cable; install the USB driver |
| Component not found | Check the network; `main/idf_component.yml` must list `viewesmart/bsp_uedx80480043_wb_a: "^1.0.0"` |
| Garbled LCD | Target must be esp32s3; 480×272 needs the panel option above |
| Wi-Fi never joins | Use a **2.4 GHz** AP only (not 5 GHz) |

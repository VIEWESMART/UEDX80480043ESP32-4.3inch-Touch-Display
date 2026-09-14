# 01_i2c_scan

[English](README.md) | [中文](README_CN.md)

Scans the onboard touch I2C bus (SDA=GPIO19, SCL=GPIO20) to confirm **GT911** is present.

The BSP comes from the registry: [viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a) (downloaded on the first build).

Full first-time software setup: [../README.md](../README.md).

---

## What you need

- The board and a data-capable USB Type-C cable
- VS Code with **ESP-IDF 5.5 or newer** installed via **EIM**

### First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Extensions: search `ESP-IDF`, install the one by **Espressif**
3. Press **F1** → **ESP-IDF: Open ESP-IDF Installation Manager**
4. **Easy Installation**, pick **IDF 5.5 or newer**, wait until it finishes
5. The dashboard lists that version; the VS Code status bar shows `v5.5.x`
6. Restart VS Code if needed

---

## Steps

1. **File → Open Folder** and select only `01_i2c_scan` (not the parent `examples` folder)
2. Plug in USB
3. F1 → **ESP-IDF: Set Espressif Device Target** → **esp32s3**
4. F1 → **ESP-IDF: Select Port to Use** → pick the COM / tty port
5. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device** (`Ctrl+E` then `D`)

The first build downloads the BSP. `Project build complete` with no red `FAILED` means the build succeeded.

---

## How you know it worked

The monitor should print an address map and find GT911. Typical success log:

```
I (xxx) i2c_scan: I2C scan: SDA=19 SCL=20
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
50: -- -- -- -- -- 5d -- -- -- -- -- -- -- -- -- --
I (xxx) i2c_scan: found device at 0x5D
I (xxx) i2c_scan: scan done, 1 device(s). GT911 expected 0x5D or 0x14
```

- **OK:** `found device at 0x5D` or `0x14`, and `scan done` reports at least one device
- **Fail:** only `--` in the table and `0 device(s)` — check the USB cable, touch flex, and RST (GPIO38)

Some modules use `0x14` instead of `0x5D`. Either address is fine.

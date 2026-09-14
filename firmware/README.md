# Firmware

Prebuilt images for the Espressif flash download tool in `tools/`. There is **no** version number inside the `.bin` files; use this table.

| File | What it is | Current IDF example |
| --- | --- | --- |
| `lvgl_v9_demo_4_3inch.bin` | LVGL widgets demo | [`examples/esp_idf/05_display_lvgl_port`](../examples/esp_idf/05_display_lvgl_port) |
| `squareline_coffee_4_3inch.bin` | SquareLine coffee UI (800×480) | [`examples/esp_idf/07_squareline_coffee`](../examples/esp_idf/07_squareline_coffee) |
| `gui_guider_monitoring_4_3inch.bin` | GUI Guider monitor UI (800×480) | [`examples/esp_idf/08_gui_guider_monitoring`](../examples/esp_idf/08_gui_guider_monitoring) |

These binaries were produced from the **previous** IDF sample tree (local `hw_init`, older folder names). The current examples use BSP `viewesmart/bsp_uedx80480043_wb_a` from the Component Registry and **ESP-IDF 5.5+**. Flash a bin for a quick screen check; for the latest behavior, build the matching folder under `examples/esp_idf`.

There are no prebuilt images for `01_i2c_scan`, `02_wifi`, `03_ble`, `04_sd`, or `06_album`.

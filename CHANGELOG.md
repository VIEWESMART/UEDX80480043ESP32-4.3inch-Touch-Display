# Changelog

All notable changes to this board repository are documented here.

## [2026-09-14]

### ESP-IDF examples (breaking)

Replaced the old IDF sample folders with eight standalone projects under [`examples/esp_idf`](examples/esp_idf). Each example pulls BSP [`viewesmart/bsp_uedx80480043_wb_a`](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a) `^1.0.0` from the Espressif Component Registry. **ESP-IDF 5.5 or newer** is required (`idf >= 5.5`).

| Old path | New path |
| --- | --- |
| `examples/esp_idf/lvgl_v9_demo_4_3inch` | [`05_display_lvgl_port`](examples/esp_idf/05_display_lvgl_port) |
| `examples/esp_idf/sd_card_spi` | [`04_sd`](examples/esp_idf/04_sd) |
| `examples/esp_idf/squareline_coffee_4_3inch` | [`07_squareline_coffee`](examples/esp_idf/07_squareline_coffee) |
| `examples/esp_idf/gui_guider_monitoring_4_3inch` | [`08_gui_guider_monitoring`](examples/esp_idf/08_gui_guider_monitoring) |

New examples: [`01_i2c_scan`](examples/esp_idf/01_i2c_scan), [`02_wifi`](examples/esp_idf/02_wifi), [`03_ble`](examples/esp_idf/03_ble), [`06_album`](examples/esp_idf/06_album).

First-time VS Code + EIM steps: [examples/esp_idf/README.md](examples/esp_idf/README.md).

Open **one** numbered folder as the workspace (not `examples/` and not `examples/esp_idf`).

### Firmware

Prebuilt binaries in [`firmware/`](firmware/) still use the old file names. Mapping:

| Binary | Current example |
| --- | --- |
| `lvgl_v9_demo_4_3inch.bin` | `05_display_lvgl_port` |
| `squareline_coffee_4_3inch.bin` | `07_squareline_coffee` |
| `gui_guider_monitoring_4_3inch.bin` | `08_gui_guider_monitoring` |

These images were built from the previous tree. For the registry-BSP examples, build from source under `examples/esp_idf`.

### Docs

- Root README section 4 (Software) updated for the new IDF examples and IDF 5.5+.
- Arduino and PlatformIO examples are unchanged.

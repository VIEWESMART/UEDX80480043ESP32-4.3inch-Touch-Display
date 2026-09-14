# 变更说明

本开发板仓库的重要变更记录如下。

## [2026-09-14]

### ESP-IDF 示例（不兼容旧路径）

原 IDF 示例目录已替换为 [`examples/esp_idf`](examples/esp_idf) 下 **8 个独立工程**。每个示例从乐鑫组件仓库拉取 BSP [`viewesmart/bsp_uedx80480043_wb_a`](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a) `^1.0.0`。需要 **ESP-IDF 5.5 或更新**（`idf >= 5.5`）。

| 旧路径 | 新路径 |
| --- | --- |
| `examples/esp_idf/lvgl_v9_demo_4_3inch` | [`05_display_lvgl_port`](examples/esp_idf/05_display_lvgl_port) |
| `examples/esp_idf/sd_card_spi` | [`04_sd`](examples/esp_idf/04_sd) |
| `examples/esp_idf/squareline_coffee_4_3inch` | [`07_squareline_coffee`](examples/esp_idf/07_squareline_coffee) |
| `examples/esp_idf/gui_guider_monitoring_4_3inch` | [`08_gui_guider_monitoring`](examples/esp_idf/08_gui_guider_monitoring) |

新增：[`01_i2c_scan`](examples/esp_idf/01_i2c_scan)、[`02_wifi`](examples/esp_idf/02_wifi)、[`03_ble`](examples/esp_idf/03_ble)、[`06_album`](examples/esp_idf/06_album)。

第一次用 VS Code + EIM：[examples/esp_idf/README_CN.md](examples/esp_idf/README_CN.md)。

请只打开**某一个**带编号的文件夹作为工作区（不要打开 `examples/` 或整个 `examples/esp_idf`）。

### 预编译固件

[`firmware/`](firmware/) 里的 bin 仍使用旧文件名，对应关系：

| 固件文件 | 当前示例 |
| --- | --- |
| `lvgl_v9_demo_4_3inch.bin` | `05_display_lvgl_port` |
| `squareline_coffee_4_3inch.bin` | `07_squareline_coffee` |
| `gui_guider_monitoring_4_3inch.bin` | `08_gui_guider_monitoring` |

这些镜像来自改版前的工程。要跑注册表 BSP 的新示例，请在 `examples/esp_idf` 里自行编译。

### 文档

- 根目录 README 第 4 节（软件）已按新 IDF 示例和 IDF 5.5+ 更新。
- Arduino、PlatformIO 示例未改。

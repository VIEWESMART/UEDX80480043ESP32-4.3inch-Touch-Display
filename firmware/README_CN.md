# 预编译固件

配合 `tools/` 里的乐鑫烧录工具使用。`.bin` 文件内部**没有**版本号，请按下表选择。

| 文件 | 内容 | 当前 IDF 示例 |
| --- | --- | --- |
| `lvgl_v9_demo_4_3inch.bin` | LVGL Widgets 演示 | [`examples/esp_idf/05_display_lvgl_port`](../examples/esp_idf/05_display_lvgl_port) |
| `squareline_coffee_4_3inch.bin` | SquareLine 咖啡机界面（800×480） | [`examples/esp_idf/07_squareline_coffee`](../examples/esp_idf/07_squareline_coffee) |
| `gui_guider_monitoring_4_3inch.bin` | GUI Guider 监控界面（800×480） | [`examples/esp_idf/08_gui_guider_monitoring`](../examples/esp_idf/08_gui_guider_monitoring) |

这些镜像来自**改版前**的 IDF 示例（本地 `hw_init`、旧目录名）。当前示例使用组件仓库 BSP `viewesmart/bsp_uedx80480043_wb_a`，需要 **ESP-IDF 5.5+**。快速点屏可烧这些 bin；要最新行为请在 `examples/esp_idf` 对应目录自行编译。

`01_i2c_scan`、`02_wifi`、`03_ble`、`04_sd`、`06_album` 没有预编译固件。

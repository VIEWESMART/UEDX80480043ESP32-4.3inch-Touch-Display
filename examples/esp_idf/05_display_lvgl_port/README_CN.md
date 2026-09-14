# 05_display_lvgl_port

[English](README.md) | [中文](README_CN.md)

点亮 4.3 寸 RGB 屏，用 `bsp_display_start()` 和 `esp_lvgl_adapter` 运行 **LVGL Widgets** 演示，触摸芯片为 GT911。

BSP：[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)。装软件见 [../README_CN.md](../README_CN.md)。

默认分辨率 **800×480**。若是 480×272 模组，见文末换屏。

---

## 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 扩展安装 **ESP-IDF**（Espressif）
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**
4. IDF 选 **5.5 或更新**（本示例还需要 PSRAM，工程 defaults 已打开）
5. 状态栏出现 `v5.5.x` 即装好

---

## 使用步骤

1. **文件 → 打开文件夹**，只打开 `05_display_lvgl_port`
2. USB 接板子；Target **esp32s3**；选 COM 口
3. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

第一次编译会下载 BSP、LVGL、`esp_lvgl_adapter`，时间较长。成功：`Project build complete`，无 `FAILED`。

---

## 怎样判断成功

**眼睛看：** 背光亮，屏幕出现彩色控件（按钮、滑条、图表等），手指点屏幕有反应。

**串口看：**

```
I (xxx) lvgl_port: display + LVGL via esp_lvgl_adapter  800x480
I (xxx) BSP: Initializing RGB LCD UEDX80480043: 800x480 RGB565, ...
I (xxx) BSP: RGB LCD initialized
I (xxx) BSP: GT911 found at 0x5D
I (xxx) BSP: GT911 touch initialized
I (xxx) BSP: Display registered to esp_lvgl_adapter: 800x480
I (xxx) lvgl_port: LVGL widgets running, touch GT911 to interact
```

- **成功：** 有 `RGB LCD initialized`、`Display registered`、`LVGL widgets running`；屏上有界面且可触摸  
  （GT911 也可能是 `0x14`）
- **失败：** `bsp_display_start failed` —— 查 USB、IDF 是否 5.5+、target 是否 esp32s3  
  花屏/漂移 —— 确认 PSRAM 相关选项（本示例 `sdkconfig.defaults` 已包含）；480×272 必须换面板  
  有画面但摸不动 —— 先跑 `01_i2c_scan` 看触摸是否在线

---

## 换 480×272 屏幕

F1 → **ESP-IDF: SDK Configuration Editor (menuconfig)** → **Component config → Board Support Package → Display → 4.3" LCD panel** → 选 `UEDX48270043 480x272` → 保存后重新编译烧录。

也可在本目录 `sdkconfig.defaults` 里取消注释 `CONFIG_BSP_LCD_PANEL_480X272=y`。若已有 `sdkconfig`，改 defaults 不会生效，请先删除 `sdkconfig`。

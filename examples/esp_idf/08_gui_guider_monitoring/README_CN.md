# 08_gui_guider_monitoring

[English](README.md) | [中文](README_CN.md)

NXP GUI Guider 导出的楼宇监控界面，运行在 UEDX80480043E-WB 上。屏幕和触摸由 BSP **[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)** 初始化。

界面按 **800×480** 设计。装软件见 [../README_CN.md](../README_CN.md)。

---

## 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 扩展安装 **ESP-IDF**（Espressif）
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**
4. IDF 选 **5.5 或更新**
5. 状态栏出现 `v5.5.x` 即装好

---

## 使用步骤

1. **文件 → 打开文件夹**，只打开 `08_gui_guider_monitoring`
2. 若以前用本地 BSP 或旧工程编过，先删掉本目录的 `build`、`managed_components`、`sdkconfig`
3. USB 接板子；Target **esp32s3**；选 COM 口
4. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

图片和字体较多，第一次编译较慢。成功：`Project build complete`，无 `FAILED`。

---

## 怎样判断成功

**眼睛看：** 背光亮，出现监控首页（空调 / 照明 / 用电等），手指能点开关、切页面。

**串口看：**

```
I (xxx) guider: GUI Guider monitoring UI  800x480
I (xxx) BSP: RGB LCD initialized
I (xxx) BSP: GT911 found at 0x5D
I (xxx) BSP: Display registered to esp_lvgl_adapter: 800x480
I (xxx) guider: GUI Guider UI running, touch GT911 to interact
```

- **成功：** 有 `RGB LCD initialized` 和 `GUI Guider UI running`，屏上是监控 UI
- **失败：** `bsp_display_start failed` —— IDF ≥ 5.5、target 为 esp32s3  
  花屏 / 布局错位 —— 本 UI 按 800×480；480×272 不适合直接跑

---

## 换屏说明

本 GUI Guider 工程分辨率是 800×480。请使用 800×480 模组。

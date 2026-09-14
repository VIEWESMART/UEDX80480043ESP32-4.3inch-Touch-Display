# 07_squareline_coffee

[English](README.md) | [中文](README_CN.md)

SquareLine Studio 导出的咖啡机界面，运行在 UEDX80480043E-WB 上。屏幕和触摸由 BSP **[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)** 初始化。

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

1. **文件 → 打开文件夹**，只打开 `07_squareline_coffee`
2. 若以前用本地 BSP 或旧工程编过，先删掉本目录的 `build`、`managed_components`、`sdkconfig`
3. USB 接板子；Target **esp32s3**；选 COM 口
4. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

本示例图片较多，第一次编译会下载 BSP 并花较长时间。成功：`Project build complete`，无 `FAILED`。

---

## 怎样判断成功

**眼睛看：** 背光亮，出现咖啡机启动页 / 主界面，手指能点按钮、滑条。

**串口看：**

```
I (xxx) coffee: SquareLine coffee UI  800x480
I (xxx) BSP: RGB LCD initialized
I (xxx) BSP: GT911 found at 0x5D
I (xxx) BSP: Display registered to esp_lvgl_adapter: 800x480
I (xxx) coffee: SquareLine UI running, touch GT911 to interact
```

- **成功：** 有 `RGB LCD initialized` 和 `SquareLine UI running`，屏上是咖啡机 UI
- **失败：** `bsp_display_start failed` —— IDF ≥ 5.5、target 为 esp32s3  
  链接缺 `ui_init` —— 确认 `main/ui/filelist.txt` 还在  
  花屏 —— 本 UI 按 800×480；480×272 模组不适合直接跑

---

## 换屏说明

本 SquareLine 工程分辨率是 800×480。480×272 模组即使在 menuconfig 里换面板，界面也会对不齐，请用 800×480 屏。

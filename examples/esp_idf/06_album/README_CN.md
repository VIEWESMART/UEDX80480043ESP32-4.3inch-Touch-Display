# 06_album

[English](README.md) | [中文](README_CN.md)

电子相册：从 SD 卡读取 `jpg` / `jpeg` / `png` / `bmp`，全屏显示。

BSP：[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)。装软件见 [../README_CN.md](../README_CN.md)。

---

## 准备图片

1. Micro SD 格式化为 **FAT32**
2. 把图片放到卡上的 **`album` 文件夹**（推荐），或直接放在卡根目录
3. 分辨率接近屏幕（800×480 或 480×272）更流畅，JPEG 更省内存
4. 插卡后再给板上电

操作：点屏幕**左半边**上一张，**右半边**或板上 **BOOT** 键下一张。默认约每 5 秒自动切一张。

---

## 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 扩展安装 **ESP-IDF**（Espressif）
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**，IDF **≥ 5.5**
4. 状态栏出现 `v5.5.x`

---

## 使用步骤

1. **文件 → 打开文件夹**，只打开 `06_album`
2. USB 接板子；Target **esp32s3**；选 COM 口
3. 若是 480×272：menuconfig → **Component config → Board Support Package → Display → 4.3" LCD panel** → `UEDX48270043 480x272`
4. 自动播放间隔：menuconfig → **Example Configuration**（默认 5000 ms，`0` 表示关闭）
5. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

编译成功：`Project build complete`，无 `FAILED`。

---

## 怎样判断成功

**眼睛看：** 屏幕显示照片，底部有 `1 / N  文件名`；点左右或 BOOT 会换图。

**串口看：**

```
I (xxx) album: electronic album
I (xxx) BSP: SD card mounted at /sdcard
I (xxx) album: scanned /sdcard/album -> 8 image(s)
I (xxx) BSP: RGB LCD initialized
I (xxx) album: 8 image(s), tap left/right or BOOT
I (xxx) album: show [1/8] S:album/photo1.jpg
```

数字 `8` 会随你的图片数量变化。

- **成功：** 有 `SD card mounted`、`scanned ... -> N image(s)`（N>0）、`show [1/N]`，并且屏幕有图
- **失败：** `SD mount failed` —— 卡、FAT32、插紧  
  屏上文字 `No images` 或 N=0 —— 文件扩展名必须是 jpg/jpeg/png/bmp，可放在 `/album` 或根目录  
  花屏 —— 480×272 要换面板选项

---

## 换 480×272 屏幕

与 `05_display_lvgl_port` 相同：menuconfig 里选 **UEDX48270043 480x272**，或在本目录 `sdkconfig.defaults` 取消注释 `CONFIG_BSP_LCD_PANEL_480X272=y`。有旧 `sdkconfig` 就先删掉再编译。

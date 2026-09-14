# 04_sd

[English](README.md) | [中文](README_CN.md)

把 Micro SD 卡挂到 `/sdcard`，列出文件，再写读测试文件 `bsp_sd_test.txt`。

BSP：[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)。装软件见 [../README_CN.md](../README_CN.md)。

---

## 你需要

- 开发板 + USB 线
- **FAT32** 格式的 Micro SD（先插进板子再上电更稳妥）
- VS Code + EIM 安装的 ESP-IDF **≥ 5.5**

SPI 引脚：MOSI=11，MISO=13，SCLK=12，CS=10。

### 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 扩展安装 **ESP-IDF**（Espressif）
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**，IDF **≥ 5.5**
4. 状态栏出现 `v5.5.x`

---

## 使用步骤

1. SD 卡格式化为 FAT32，插入卡槽
2. **文件 → 打开文件夹**，只打开 `04_sd`
3. USB 接板子；Target **esp32s3**；选 COM 口
4. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

编译成功：`Project build complete`，无 `FAILED`。

---

## 怎样判断成功

```
I (xxx) sd: SD SPI example  MOSI=11 MISO=13 SCLK=12 CS=10
I (xxx) BSP: SD card mounted at /sdcard
I (xxx) sd: listing /sdcard
I (xxx) sd:   ...
I (xxx) sd: wrote /sdcard/bsp_sd_test.txt
I (xxx) sd: read back: UEDX80480043 SD test OK
I (xxx) sd: SD test done
```

- **成功：** 有 `SD card mounted`、`wrote`、`read back: UEDX80480043 SD test OK`、`SD test done`
- **失败：** `mount failed` —— 卡是否插好、是否为 FAT32（exFAT 往往不行）、是否接触不良

拔卡在电脑上打开，应能看到 `bsp_sd_test.txt`，内容为 `UEDX80480043 SD test OK`。

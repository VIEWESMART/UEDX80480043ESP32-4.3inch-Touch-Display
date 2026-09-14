# 01_i2c_scan

[English](README.md) | [中文](README_CN.md)

本示例扫描板上触摸芯片用的 I2C 总线（SDA=GPIO19，SCL=GPIO20），确认 **GT911** 在线。

BSP 来自组件仓库：[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)（第一次编译会自动下载）。

更完整的装软件步骤见 [../README_CN.md](../README_CN.md)。

---

## 你需要

- 开发板 + 能传数据的 USB Type-C 线
- VS Code，并已用 **EIM** 装好 **ESP-IDF 5.5 或更新**

还没装过 IDF？按下面做一次即可（各示例通用）。

### 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 左侧扩展里搜索 `ESP-IDF`，安装 **Espressif** 出品的扩展
3. 按 **F1**，运行 **ESP-IDF: Open ESP-IDF Installation Manager**
4. 选 **Easy Installation**，IDF 版本选 **5.5 或更新**，等安装完成
5. 仪表盘里能看到该版本；VS Code 最底下状态栏出现 `v5.5.x` 即表示成功
6. 建议重启一次 VS Code

---

## 使用步骤

1. **文件 → 打开文件夹**，只打开本目录 `01_i2c_scan`（不要打开上一级 `examples`）
2. USB 接好板子
3. F1 → **ESP-IDF: Set Espressif Device Target** → **esp32s3**
4. F1 → **ESP-IDF: Select Port to Use** → 选对应 COM 口
5. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**（编译 + 烧录 + 串口监视，快捷键 `Ctrl+E` 再按 `D`）

第一次编译较慢，会下载 BSP。终端出现 `Project build complete` 且没有红色 `FAILED`，说明编译成功。

---

## 怎样判断成功

监视窗口里应出现地址表，并且找到 GT911。常见成功日志：

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

- **成功：** 有 `found device at 0x5D` 或 `0x14`，且 `scan done` 的设备数 ≥ 1
- **失败：** 整表都是 `--`，`scan done, 0 device(s)` —— 检查 USB 是否只供电、触摸排线、RST（GPIO38）

有的模组地址是 `0x14` 而不是 `0x5D`，两种都算正常。

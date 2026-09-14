# VIEWE 4.3 寸示例（给第一次用的人）

[English](README.md) | [中文](README_CN.md)

这些示例都使用乐鑫组件仓库里的 BSP，**不再依赖本机旁边的源码文件夹**：

[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a) `^1.0.0`

第一次编译时，VS Code / IDF 会自动从网上把 BSP 下载到该示例的 `managed_components/` 目录。每个示例只依赖本目录文件（板级 Flash / PSRAM 等已写进该示例自己的 `sdkconfig.defaults`），不要再引用仓库里其它本地路径。

| 文件夹 | 做什么 | 怎样算成功 |
| --- | --- | --- |
| [01_i2c_scan](01_i2c_scan/README_CN.md) | 扫描触摸芯片 | 串口出现 `0x5D` 或 `0x14` |
| [02_wifi](02_wifi/README_CN.md) | 连接家里的 2.4 GHz Wi-Fi | 串口出现 `Wi-Fi got IP` |
| [03_ble](03_ble/README_CN.md) | 手机蓝牙配对 | 能搜到 `UEDX-4.3-S3` 并配对成功 |
| [04_sd](04_sd/README_CN.md) | 读写 Micro SD | 串口出现 `SD test done` |
| [05_display_lvgl_port](05_display_lvgl_port/README_CN.md) | 点亮屏幕 + 触摸 | 屏幕出现控件，手指能点 |
| [06_album](06_album/README_CN.md) | SD 卡电子相册 | 屏幕显示图片 |
| [07_squareline_coffee](07_squareline_coffee/README_CN.md) | SquareLine 咖啡机 UI | 屏幕出现咖啡机界面，可触摸 |
| [08_gui_guider_monitoring](08_gui_guider_monitoring/README_CN.md) | GUI Guider 监控 UI | 屏幕出现监控首页，可触摸 |

每个示例文件夹里都有中英文 README，可以只打开那一个文件夹跟着做。下面是**第一次**要装的软件，各示例都一样。

---

## 你需要准备

1. 开发板：UEDX80480043E-WB（800×480）或同一 PCB 的 UEDX48270043（480×272）
2. USB Type-C 数据线（要能传数据，不要只用充电线）
3. Windows 电脑（也可 Mac / Linux，按钮名字差不多）
4. 能上网（第一次会下载 IDF 工具和 BSP）

---

## 第一次：用 EIM 安装 ESP-IDF，再用 VS Code 操作

### 1. 安装 VS Code

打开 [https://code.visualstudio.com/](https://code.visualstudio.com/) 下载安装。一路下一步即可。

### 2. 安装 ESP-IDF 扩展

1. 打开 VS Code
2. 左侧点四个方块的 **扩展**
3. 搜索 `ESP-IDF`
4. 安装发布者是 **Espressif** 的那一个（全称一般是 *ESP-IDF*）

### 3. 用 EIM 安装 ESP-IDF（不要自己解压 zip）

EIM = Espressif Installation Manager（乐鑫安装管理器）。扩展装好后，用它来装编译器、Python、IDF 源码。

1. 按键盘 **F1**（或 `Ctrl+Shift+P`），打开命令面板
2. 输入并选择：**ESP-IDF: Open ESP-IDF Installation Manager**
3. 会弹出 EIM 窗口。选 **Easy Installation**（简易安装）
4. 点 **Start Installation** / **开始安装**
5. **IDF 版本请选 5.5 或更新**（本 BSP 要求 `idf >= 5.5`）。例如 5.5.4
6. 网络：国内可优先选乐鑫镜像；失败再换 GitHub
7. 等待进度条走完（可能十几分钟到一小时，看网速）
8. 完成后点 **Go to Dashboard**。列表里能看到你刚装的版本，例如 `v5.5.4`
9. 关掉 EIM。建议重启一次 VS Code

怎样判断 IDF 装好了：

- EIM 仪表盘里该版本旁边是已安装 / ready
- VS Code **最底下状态栏** 会出现 ESP-IDF 版本号（例如 `v5.5.4`），而不是一直转圈或报 *IDF is not configured*

### 4. 打开某一个示例（不要打开整个 `esp_idf` 文件夹）

每个 `01_i2c_scan`、`02_wifi` … 都是**独立工程**。

1. VS Code 菜单 **文件 → 打开文件夹**
2. 只选中一个示例，例如 `...\examples\esp_idf\01_i2c_scan`
3. 若提示“是否信任此文件夹”，选信任

打开错了（打开了上一级 `examples` 或整个 `esp_idf`）时，编译会找不到工程。关掉窗口，重新只打开一个示例文件夹。

### 5. 选芯片和串口

1. 用 USB-C 把板子连到电脑，板子上电
2. F1 → **ESP-IDF: Set Espressif Device Target** → 选 **esp32s3**
3. F1 → **ESP-IDF: Select Port to Use** → 选这个板子对应的 COM 口  
   Windows 可在“设备管理器 → 端口”里看，常见是 USB JTAG / USB Serial / USB 串行设备

状态栏应类似：`v5.5.x` · `esp32s3` · `COM3`（数字因电脑而异）

### 6. 编译、烧录、看串口

状态栏或命令面板都可以：

| 你想做的事 | 命令面板里搜 |
| --- | --- |
| 只编译 | **ESP-IDF: Build your Project** |
| 烧录到板子 | **ESP-IDF: Flash your Project** |
| 看串口日志 | **ESP-IDF: Monitor Device**（或 `Ctrl+E` 再按 `M`） |
| 三步一起做 | **ESP-IDF: Build, Flash and Start a Monitor on Your Device**（或 `Ctrl+E` 再按 `D`） |

也可以点窗口**最底下状态栏**的锤子（编译）、闪电（烧录）、插头（监视）。

第一次编译会下载 BSP 和依赖，时间较长。成功编译结束时，终端里会出现类似：

```
Project build complete. To flash, run:
idf.py -p COMx flash
```

或 `Creating esp32s3 image...` 且最后没有红色 `FAILED`。

烧录时板子要连着 USB。若卡住，按一下板上 **BOOT** 再试，或断电重插 USB。

串口监视默认 **115200**。要退出监视：在监视终端里按 `Ctrl+]`。

### 7. 以前用本地 BSP 编过？

把依赖改成注册表之后，请删掉该示例里的 `build`、`managed_components` 和 `sdkconfig`，再重新编译，否则可能还在用旧的本地组件或旧板级配置。

---

## 换屏幕（480×272）

默认按 **800×480**。若你是 UEDX48270043（480×272）：

1. F1 → **ESP-IDF: SDK Configuration Editor (menuconfig)**
2. 打开 **Component config → Board Support Package → Display → 4.3" LCD panel**
3. 改成 `UEDX48270043 480x272`
4. 保存，再编译烧录

也可在该示例自己的 `sdkconfig.defaults` 里取消注释 `CONFIG_BSP_LCD_PANEL_480X272=y`。改完若已有 `sdkconfig`，先删掉再编译。`07` / `08` 的界面按 800×480 设计，不要在 480×272 上硬跑。

---

## 常见问题

| 现象 | 怎么办 |
| --- | --- |
| 扩展提示 IDF 未配置 | 再跑一遍 EIM，装完重启 VS Code |
| 找不到 COM 口 | 换能传数据的 USB 线；装 USB 驱动；看设备管理器 |
| 编译失败找不到组件 | 确认已联网；看 `main/idf_component.yml` 是否为 `viewesmart/bsp_uedx80480043_wb_a: "^1.0.0"` |
| 花屏 / 乱线 | 确认已设 target 为 esp32s3；480×272 要换面板选项 |
| Wi-Fi 连不上 | 必须是 **2.4 GHz**，5 GHz 不行 |

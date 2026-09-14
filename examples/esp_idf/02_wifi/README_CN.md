# 02_wifi

[English](README.md) | [中文](README_CN.md)

把开发板连到你家 **2.4 GHz** Wi-Fi（5 GHz 连不上）。连上后串口会打印 IP 地址。

BSP：[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)。装软件见 [../README_CN.md](../README_CN.md)。

---

## 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 扩展搜索 `ESP-IDF`，安装 **Espressif** 出品
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**
4. IDF 选 **5.5 或更新**，装完后状态栏出现 `v5.5.x`

---

## 使用步骤

1. **文件 → 打开文件夹**，只打开 `02_wifi`
2. **先改 Wi-Fi 名称和密码**（二选一）

**方法 A（推荐）：** 用 VS Code 打开本目录的 `sdkconfig.defaults`，改这两行（引号要保留）：

```
CONFIG_EXAMPLE_WIFI_SSID="你家的WiFi"
CONFIG_EXAMPLE_WIFI_PASSWORD="密码"
```

如果以前编译过，请删掉本目录的 `sdkconfig`（以及 `sdkconfig.old`），否则改 defaults **不会生效**。

**方法 B：** F1 → **ESP-IDF: SDK Configuration Editor (menuconfig)** → **Example Configuration** → WiFi SSID / WiFi Password，保存后再编译。

这是本示例自己的选项，和 BSP 菜单里的 `CONFIG_BSP_WIFI_*` 不是同一组。

3. USB 接板子
4. F1 → Target 选 **esp32s3**，再选 COM 口
5. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

编译成功：终端有 `Project build complete`，无 `FAILED`。

---

## 怎样判断成功

```
I (xxx) wifi: Wi-Fi STA example
I (xxx) wifi: SSID="你家的WiFi"
I (xxx) BSP: Wi-Fi STA connecting to "你家的WiFi"
I (xxx) BSP: Wi-Fi got IP: 192.168.1.23
I (xxx) wifi: IP: 192.168.1.23  mask: 255.255.255.0  gw: 192.168.1.1
I (xxx) wifi: connected=1 rssi probe
```

- **成功：** 出现 `Wi-Fi got IP` 和 `connected=1`，IP 不是 `0.0.0.0`
- **失败：** `connect timeout` 或一直 `waiting for IP`  
  - SSID/密码是否改过、是否删了旧 `sdkconfig`  
  - 路由器是否为 **2.4 GHz**（名称里带 5G 的往往不行）  
  - 是否仍是占位符 `myssid` / `mypassword`

板子只有 2.4 GHz Wi-Fi。ESP32-S3 的 Wi-Fi 和蓝牙不能同时全速工作。

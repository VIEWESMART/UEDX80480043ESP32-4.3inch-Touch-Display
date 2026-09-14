# 03_ble

[English](README.md) | [中文](README_CN.md)

开发板作为 BLE GATT 服务器，设备名 **`UEDX-4.3-S3`**。手机用系统蓝牙或 nRF Connect / LightBlue **直接配对**（Just Works，不用输 PIN）。

BSP：[viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a)。装软件见 [../README_CN.md](../README_CN.md)。

---

## 第一次安装（EIM + VS Code）

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 扩展安装 **ESP-IDF**（Espressif）
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**，IDF **≥ 5.5**
4. 状态栏出现 `v5.5.x` 即装好

---

## 使用步骤

1. **文件 → 打开文件夹**，只打开 `03_ble`
2. USB 接板子；Target 选 **esp32s3**；选好 COM 口
3. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**
4. 编译成功：终端有 `Project build complete`，无 `FAILED`
5. 若以前配对失败过，先在手机蓝牙里 **忽略 / 取消配对** 该设备
6. 手机打开蓝牙，扫描 **UEDX-4.3-S3**，点连接 / 配对（不用输入密码）

iPhone 的系统蓝牙列表经常不显示普通 BLE 设备，请用 **nRF Connect** 或 **LightBlue**。

GATT：服务 `0x00FF`，特征 `0xFF01`（加密后可读可写）。用 nRF Connect 读写该特征会触发配对。

---

## 怎样判断成功

烧录后、还没连手机时：

```
I (xxx) ble: BLE GATT server + Just Works pairing
I (xxx) BSP: Bluetooth BLE + Bluedroid initialized
I (xxx) ble: GATT service 0x00FF started
I (xxx) ble: advertising started, name=UEDX-4.3-S3
I (xxx) ble: ready. Phone: scan UEDX-4.3-S3, connect, then pair (Just Works, no PIN)
```

手机连上并配对成功后还会出现：

```
I (xxx) ble: connected, conn_id=0, remote xx:xx:xx:xx:xx:xx
I (xxx) ble: pairing request, accept
I (xxx) ble: key exchanged, type=0x1
I (xxx) ble: auth complete, ... success=1 ...
I (xxx) ble: pairing OK, bonded devices=1
```

- **成功：** 有 `advertising started`；配对后有 `pairing OK` 且 `success=1`
- **失败：** 搜不到名字 —— 确认已烧录本示例、手机离板子近；iOS 请换 nRF Connect  
  配对马上断开且 `pairing failed` —— 在手机上忘掉该设备再试

ESP32-S3 的 Wi-Fi 与 BLE 共用射频，不要同时跑 Wi-Fi 示例。

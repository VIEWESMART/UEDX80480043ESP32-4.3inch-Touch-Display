# 02_wifi

[English](README.md) | [中文](README_CN.md)

Joins a **2.4 GHz** Wi-Fi AP (5 GHz will not work) and prints the IP address.

BSP: [viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a). First-time setup: [../README.md](../README.md).

---

## First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Extensions: `ESP-IDF` by **Espressif**
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**
4. Pick **IDF 5.5 or newer**. The status bar should show `v5.5.x`

---

## Steps

1. **File → Open Folder** and select only `02_wifi`
2. **Set SSID and password** (pick one way)

**A (recommended):** edit `sdkconfig.defaults` in this folder:

```
CONFIG_EXAMPLE_WIFI_SSID="your_ssid"
CONFIG_EXAMPLE_WIFI_PASSWORD="your_password"
```

If you already built once, delete `sdkconfig` (and `sdkconfig.old`) or the new defaults will **not** apply.

**B:** F1 → **ESP-IDF: SDK Configuration Editor (menuconfig)** → **Example Configuration** → WiFi SSID / password, save, then build.

These are this example’s options, not `CONFIG_BSP_WIFI_*` in the BSP menu.

3. Plug in USB
4. Target **esp32s3**, then select the serial port
5. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**

A good build prints `Project build complete` with no `FAILED`.

---

## How you know it worked

```
I (xxx) wifi: Wi-Fi STA example
I (xxx) wifi: SSID="your_ssid"
I (xxx) BSP: Wi-Fi STA connecting to "your_ssid"
I (xxx) BSP: Wi-Fi got IP: 192.168.1.23
I (xxx) wifi: IP: 192.168.1.23  mask: 255.255.255.0  gw: 192.168.1.1
I (xxx) wifi: connected=1 rssi probe
```

- **OK:** `Wi-Fi got IP` and `connected=1`, IP is not `0.0.0.0`
- **Fail:** `connect timeout` or endless `waiting for IP`  
  - Did you change SSID/password and delete the old `sdkconfig`?  
  - Is the AP **2.4 GHz** (names with “5G” often are not)?  
  - Still using the placeholders `myssid` / `mypassword`?

This board has 2.4 GHz Wi-Fi only. Wi-Fi and BLE share the RF front-end on ESP32-S3.

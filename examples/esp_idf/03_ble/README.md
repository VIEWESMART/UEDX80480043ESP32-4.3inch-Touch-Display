# 03_ble

[English](README.md) | [中文](README_CN.md)

The board runs a BLE GATT server named **`UEDX-4.3-S3`**. Pair from the phone with **Just Works** (no PIN), using system Bluetooth or nRF Connect / LightBlue.

BSP: [viewesmart/bsp_uedx80480043_wb_a](https://components.espressif.com/components/viewesmart/bsp_uedx80480043_wb_a). First-time setup: [../README.md](../README.md).

---

## First-time install (EIM + VS Code)

1. Install [VS Code](https://code.visualstudio.com/)
2. Install the **ESP-IDF** extension (Espressif)
3. F1 → **ESP-IDF: Open ESP-IDF Installation Manager** → **Easy Installation**, IDF **≥ 5.5**
4. Status bar shows `v5.5.x`

---

## Steps

1. **File → Open Folder** → only `03_ble`
2. USB in; target **esp32s3**; select the serial port
3. F1 → **ESP-IDF: Build, Flash and Start a Monitor on Your Device**
4. Build OK: `Project build complete`, no `FAILED`
5. If a previous pairing failed, **Forget / unpair** the device on the phone first
6. Scan for **UEDX-4.3-S3** and connect / pair (no PIN)

iOS Settings → Bluetooth often hides generic BLE peripherals. Use **nRF Connect** or **LightBlue**.

GATT: service `0x00FF`, characteristic `0xFF01` (encrypted read/write). Reading/writing it in nRF Connect starts pairing.

---

## How you know it worked

Right after flash, before the phone connects:

```
I (xxx) ble: BLE GATT server + Just Works pairing
I (xxx) BSP: Bluetooth BLE + Bluedroid initialized
I (xxx) ble: GATT service 0x00FF started
I (xxx) ble: advertising started, name=UEDX-4.3-S3
I (xxx) ble: ready. Phone: scan UEDX-4.3-S3, connect, then pair (Just Works, no PIN)
```

After a successful pair:

```
I (xxx) ble: connected, conn_id=0, remote xx:xx:xx:xx:xx:xx
I (xxx) ble: pairing request, accept
I (xxx) ble: key exchanged, type=0x1
I (xxx) ble: auth complete, ... success=1 ...
I (xxx) ble: pairing OK, bonded devices=1
```

- **OK:** `advertising started`; then `pairing OK` with `success=1`
- **Fail:** name not in the scan list — confirm this firmware is running; iOS needs nRF Connect  
  Immediate disconnect and `pairing failed` — forget the device on the phone and retry

Wi-Fi and BLE share RF on ESP32-S3; do not run the Wi-Fi example at the same time.

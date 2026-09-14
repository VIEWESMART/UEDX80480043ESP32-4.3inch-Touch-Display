/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * BLE GATT Server + Just Works pairing.
 * Phone: scan "UEDX-4.3-S3", connect, then pair.
 *
 * The old advertise-only example had no GATT service and did not
 * handle SEC_REQ / encryption, so system Bluetooth pairing failed.
 */

#include <inttypes.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt_defs.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gatt_common_api.h"
#include "esp_bt_device.h"
#include "bsp/bsp_uedx80480043_wb_a.h"

static const char *TAG = "ble";
static const char *DEVICE_NAME = "UEDX-4.3-S3";

#define PROFILE_APP_ID       0
#define SVC_INST_ID          0
#define ADV_CONFIG_FLAG      (1 << 0)
#define SCAN_RSP_CONFIG_FLAG (1 << 1)
#define CHAR_VAL_LEN_MAX     32

enum {
    IDX_SVC,
    IDX_CHAR_DECL,
    IDX_CHAR_VAL,
    IDX_NB,
};

static uint8_t adv_config_done;
static uint16_t handle_table[IDX_NB];
static uint8_t char_value[CHAR_VAL_LEN_MAX] = "UEDX80480043";

/* 16-bit UUID 0x00FF encoded as 128-bit Bluetooth Base UUID (little-endian). */
static uint8_t service_uuid128[16] = {
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

/*
 * ADV is 31 bytes. Put the name in the scan response so that
 * flags + UUID128 + name + txpower do not overflow config_adv_data.
 */
static esp_ble_adv_data_t adv_data = {
    .set_scan_rsp = false,
    .include_name = false,
    .include_txpower = true,
    .min_interval = ESP_BLE_GAP_CONN_ITVL_MS(7.5),
    .max_interval = ESP_BLE_GAP_CONN_ITVL_MS(20),
    .appearance = 0x00,
    .manufacturer_len = 0,
    .p_manufacturer_data = NULL,
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = sizeof(service_uuid128),
    .p_service_uuid = service_uuid128,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static esp_ble_adv_data_t scan_rsp_data = {
    .set_scan_rsp = true,
    .include_name = true,
    .include_txpower = true,
};

static esp_ble_adv_params_t adv_params = {
    .adv_int_min = ESP_BLE_GAP_ADV_ITVL_MS(40),
    .adv_int_max = ESP_BLE_GAP_ADV_ITVL_MS(80),
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static const uint16_t primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t gatts_service_uuid = 0x00FF;
static const uint16_t gatts_char_uuid = 0xFF01;
static const uint8_t char_prop_read_write =
    ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE;

static const esp_gatts_attr_db_t gatt_db[IDX_NB] = {
    [IDX_SVC] = {
        {ESP_GATT_AUTO_RSP},
        {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
         sizeof(uint16_t), sizeof(gatts_service_uuid), (uint8_t *)&gatts_service_uuid}
    },
    [IDX_CHAR_DECL] = {
        {ESP_GATT_AUTO_RSP},
        {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
         sizeof(uint8_t), sizeof(uint8_t), (uint8_t *)&char_prop_read_write}
    },
    [IDX_CHAR_VAL] = {
        {ESP_GATT_AUTO_RSP},
        {ESP_UUID_LEN_16, (uint8_t *)&gatts_char_uuid,
         ESP_GATT_PERM_READ_ENCRYPTED | ESP_GATT_PERM_WRITE_ENCRYPTED,
         CHAR_VAL_LEN_MAX, sizeof("UEDX80480043") - 1, char_value}
    },
};

static void start_advertising(void)
{
    esp_err_t ret = esp_ble_gap_start_advertising(&adv_params);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "start advertising failed: %s", esp_err_to_name(ret));
    }
}

static void config_advertising_data(void)
{
    esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "config adv data failed: %s", esp_err_to_name(ret));
        return;
    }
    adv_config_done |= ADV_CONFIG_FLAG;

    ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "config scan rsp failed: %s", esp_err_to_name(ret));
        return;
    }
    adv_config_done |= SCAN_RSP_CONFIG_FLAG;
}

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        adv_config_done &= ~ADV_CONFIG_FLAG;
        if (adv_config_done == 0) {
            start_advertising();
        }
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        adv_config_done &= ~SCAN_RSP_CONFIG_FLAG;
        if (adv_config_done == 0) {
            start_advertising();
        }
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        if (param->adv_start_cmpl.status == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "advertising started, name=%s", DEVICE_NAME);
        } else {
            ESP_LOGE(TAG, "advertising start failed, status=0x%x", param->adv_start_cmpl.status);
        }
        break;
    case ESP_GAP_BLE_SEC_REQ_EVT:
        ESP_LOGI(TAG, "pairing request, accept");
        esp_ble_gap_security_rsp(param->ble_security.ble_req.bd_addr, true);
        break;
    case ESP_GAP_BLE_PASSKEY_REQ_EVT:
        ESP_LOGI(TAG, "passkey request, reply 0 (Just Works)");
        esp_ble_passkey_reply(param->ble_security.ble_req.bd_addr, true, 0);
        break;
    case ESP_GAP_BLE_NC_REQ_EVT:
        ESP_LOGI(TAG, "numeric comparison, passkey=%" PRIu32, param->ble_security.key_notif.passkey);
        esp_ble_confirm_reply(param->ble_security.ble_req.bd_addr, true);
        break;
    case ESP_GAP_BLE_PASSKEY_NOTIF_EVT:
        ESP_LOGI(TAG, "passkey notify: %06" PRIu32, param->ble_security.key_notif.passkey);
        break;
    case ESP_GAP_BLE_AUTH_CMPL_EVT:
        ESP_LOGI(TAG, "auth complete, addr " ESP_BD_ADDR_STR ", success=%d, reason=0x%x",
                 ESP_BD_ADDR_HEX(param->ble_security.auth_cmpl.bd_addr),
                 param->ble_security.auth_cmpl.success,
                 param->ble_security.auth_cmpl.fail_reason);
        if (param->ble_security.auth_cmpl.success) {
            ESP_LOGI(TAG, "pairing OK, bonded devices=%d", esp_ble_get_bond_device_num());
        } else {
            ESP_LOGE(TAG, "pairing failed");
        }
        break;
    case ESP_GAP_BLE_KEY_EVT:
        ESP_LOGI(TAG, "key exchanged, type=0x%x", param->ble_security.ble_key.key_type);
        break;
    default:
        break;
    }
}

static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                        esp_ble_gatts_cb_param_t *param)
{
    switch (event) {
    case ESP_GATTS_REG_EVT:
        ESP_LOGI(TAG, "GATTS register, status=%d gatts_if=%d", param->reg.status, gatts_if);
        {
            esp_err_t ret = esp_ble_gap_set_device_name(DEVICE_NAME);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "set device name failed: %s", esp_err_to_name(ret));
            }
        }
        config_advertising_data();
        {
            esp_err_t ret = esp_ble_gatts_create_attr_tab(gatt_db, gatts_if, IDX_NB, SVC_INST_ID);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "create attr tab failed: %s", esp_err_to_name(ret));
            }
        }
        break;
    case ESP_GATTS_CREAT_ATTR_TAB_EVT:
        if (param->add_attr_tab.status != ESP_GATT_OK) {
            ESP_LOGE(TAG, "create attr tab failed: 0x%x", param->add_attr_tab.status);
            break;
        }
        if (param->add_attr_tab.num_handle != IDX_NB) {
            ESP_LOGE(TAG, "attr tab handle count %d != %d", param->add_attr_tab.num_handle, IDX_NB);
            break;
        }
        memcpy(handle_table, param->add_attr_tab.handles, sizeof(handle_table));
        {
            esp_err_t ret = esp_ble_gatts_start_service(handle_table[IDX_SVC]);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "start service failed: %s", esp_err_to_name(ret));
                break;
            }
        }
        ESP_LOGI(TAG, "GATT service 0x00FF started");
        break;
    case ESP_GATTS_CONNECT_EVT:
        ESP_LOGI(TAG, "connected, conn_id=%u, remote " ESP_BD_ADDR_STR,
                 param->connect.conn_id, ESP_BD_ADDR_HEX(param->connect.remote_bda));
        /* Just Works bonding: no keyboard/display, phone can pair directly */
        {
            esp_err_t enc = esp_ble_set_encryption(param->connect.remote_bda, ESP_BLE_SEC_ENCRYPT);
            if (enc != ESP_OK) {
                ESP_LOGE(TAG, "set encryption failed: %s", esp_err_to_name(enc));
            }
        }
        break;
    case ESP_GATTS_DISCONNECT_EVT:
        ESP_LOGW(TAG, "disconnected, reason=0x%x, remote " ESP_BD_ADDR_STR,
                 param->disconnect.reason, ESP_BD_ADDR_HEX(param->disconnect.remote_bda));
        start_advertising();
        break;
    case ESP_GATTS_WRITE_EVT:
        if (!param->write.is_prep && param->write.len > 0) {
            ESP_LOGI(TAG, "char write, len=%d", param->write.len);
            ESP_LOG_BUFFER_HEX(TAG, param->write.value, param->write.len);
        }
        break;
    default:
        break;
    }
}

static struct {
    esp_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
} profile = {
    .gatts_cb = gatts_profile_event_handler,
    .gatts_if = ESP_GATT_IF_NONE,
};

static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                esp_ble_gatts_cb_param_t *param)
{
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            profile.gatts_if = gatts_if;
        } else {
            ESP_LOGE(TAG, "app register failed, status=%d", param->reg.status);
            return;
        }
    }

    if (gatts_if == ESP_GATT_IF_NONE || gatts_if == profile.gatts_if) {
        if (profile.gatts_cb) {
            profile.gatts_cb(event, gatts_if, param);
        }
    }
}

static void set_security_params(void)
{
    /* Secure Connections + Bonding, no MITM: Just Works for a board with no keypad */
    esp_ble_auth_req_t auth_req = ESP_LE_AUTH_REQ_SC_BOND;
    esp_ble_io_cap_t iocap = ESP_IO_CAP_NONE;
    uint8_t key_size = 16;
    uint8_t init_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
    uint8_t rsp_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
    uint8_t auth_option = ESP_BLE_ONLY_ACCEPT_SPECIFIED_AUTH_DISABLE;
    uint8_t oob_support = ESP_BLE_OOB_DISABLE;

    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_AUTHEN_REQ_MODE, &auth_req, sizeof(uint8_t)));
    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_IOCAP_MODE, &iocap, sizeof(uint8_t)));
    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_MAX_KEY_SIZE, &key_size, sizeof(uint8_t)));
    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH, &auth_option, sizeof(uint8_t)));
    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_OOB_SUPPORT, &oob_support, sizeof(uint8_t)));
    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_SET_INIT_KEY, &init_key, sizeof(uint8_t)));
    ESP_ERROR_CHECK(esp_ble_gap_set_security_param(ESP_BLE_SM_SET_RSP_KEY, &rsp_key, sizeof(uint8_t)));
}

void app_main(void)
{
    ESP_LOGI(TAG, "BLE GATT server + Just Works pairing");

    ESP_ERROR_CHECK(bsp_bluetooth_init());
    ESP_ERROR_CHECK(esp_ble_gatts_register_callback(gatts_event_handler));
    ESP_ERROR_CHECK(esp_ble_gap_register_callback(gap_event_handler));
    ESP_ERROR_CHECK(esp_ble_gatt_set_local_mtu(247));
    set_security_params();
    ESP_ERROR_CHECK(esp_ble_gatts_app_register(PROFILE_APP_ID));

    ESP_LOGI(TAG, "ready. Phone: scan %s, connect, then pair (Just Works, no PIN)", DEVICE_NAME);
}

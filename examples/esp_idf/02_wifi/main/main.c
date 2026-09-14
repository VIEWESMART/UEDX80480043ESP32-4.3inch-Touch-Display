/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * Wi-Fi STA connect test.
 *
 * Configure SSID/password in either:
 *   1. this example's sdkconfig.defaults (CONFIG_EXAMPLE_WIFI_SSID / PASSWORD)
 *   2. idf.py menuconfig -> Example Configuration
 */

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "sdkconfig.h"
#include "bsp/bsp_uedx80480043_wb_a.h"

static const char *TAG = "wifi";

static void log_ip(void)
{
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    if (!netif) {
        return;
    }

    esp_netif_ip_info_t ip = {0};
    if (esp_netif_get_ip_info(netif, &ip) == ESP_OK) {
        ESP_LOGI(TAG, "IP: " IPSTR "  mask: " IPSTR "  gw: " IPSTR,
                 IP2STR(&ip.ip), IP2STR(&ip.netmask), IP2STR(&ip.gw));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Wi-Fi STA example");
    ESP_LOGI(TAG, "SSID=\"%s\"", CONFIG_EXAMPLE_WIFI_SSID);

    if (CONFIG_EXAMPLE_WIFI_SSID[0] == '\0' ||
        strcmp(CONFIG_EXAMPLE_WIFI_SSID, "myssid") == 0) {
        ESP_LOGW(TAG, "Set Wi-Fi SSID/password first:");
        ESP_LOGW(TAG, "  examples/02_wifi/sdkconfig.defaults");
        ESP_LOGW(TAG, "  or idf.py menuconfig -> Example Configuration");
    }

    ESP_ERROR_CHECK(bsp_wifi_connect(CONFIG_EXAMPLE_WIFI_SSID, CONFIG_EXAMPLE_WIFI_PASSWORD));

    for (int i = 0; i < 30; i++) {
        if (bsp_wifi_is_connected()) {
            log_ip();
            break;
        }
        ESP_LOGI(TAG, "waiting for IP... %d", i + 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    if (!bsp_wifi_is_connected()) {
        ESP_LOGE(TAG, "connect timeout. Check SSID/password and 2.4 GHz AP.");
    }

    while (1) {
        ESP_LOGI(TAG, "connected=%d rssi probe", bsp_wifi_is_connected());
        if (bsp_wifi_is_connected()) {
            log_ip();
        }
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

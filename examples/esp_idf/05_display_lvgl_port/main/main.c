/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * RGB LCD + GT911 via espressif/esp_lvgl_adapter.
 * Resolution follows the BSP panel option: UEDX80480043 800x480 / UEDX48270043 480x272.
 */

#include "esp_log.h"
#include "bsp/bsp_uedx80480043_wb_a.h"
#include "lv_demos.h"

static const char *TAG = "lvgl_port";

void app_main(void)
{
    ESP_LOGI(TAG, "display + LVGL via esp_lvgl_adapter  %dx%d", BSP_LCD_H_RES, BSP_LCD_V_RES);

    lv_display_t *disp = bsp_display_start();
    if (disp == NULL) {
        ESP_LOGE(TAG, "bsp_display_start failed");
        return;
    }

    if (bsp_display_lock(-1)) {
        lv_demo_widgets();
        bsp_display_unlock();
    }

    ESP_LOGI(TAG, "LVGL widgets running, touch GT911 to interact");
}

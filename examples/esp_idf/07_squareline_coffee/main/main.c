/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * SquareLine Studio coffee-machine UI on UEDX80480043E-WB.
 * Display/touch come from viewesmart/bsp_uedx80480043_wb_a.
 */

#include "esp_log.h"
#include "bsp/esp-bsp.h"
#include "ui.h"
#include "app_features.h"
#if APP_ENABLE_COLOR_TEST
#include "iot_button.h"
#include "button_gpio.h"
#include "color_test.h"
#endif

static const char *TAG = "coffee";

#if APP_ENABLE_COLOR_TEST
static void gpio0_single_click_cb(void *button_handle, void *usr_data)
{
    (void)button_handle;
    (void)usr_data;
    if (bsp_display_lock(-1)) {
        color_test_toggle();
        bsp_display_unlock();
    }
}
#endif

void app_main(void)
{
    ESP_LOGI(TAG, "SquareLine coffee UI  %dx%d", BSP_LCD_H_RES, BSP_LCD_V_RES);

    lv_display_t *disp = bsp_display_start();
    if (disp == NULL) {
        ESP_LOGE(TAG, "bsp_display_start failed");
        return;
    }

    if (bsp_display_lock(-1)) {
        ui_init();
#if APP_ENABLE_COLOR_TEST
        color_test_init(lv_screen_active());
#endif
        bsp_display_unlock();
    }

    ESP_LOGI(TAG, "SquareLine UI running, touch GT911 to interact");

#if APP_ENABLE_COLOR_TEST
    const button_config_t btn_cfg = {0};
    const button_gpio_config_t btn_gpio_cfg = {
        .gpio_num = BSP_BUTTON_BOOT_IO,
        .active_level = 0,
        .enable_power_save = false,
        .disable_pull = false,
    };
    button_handle_t gpio0_btn = NULL;
    ESP_ERROR_CHECK(iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &gpio0_btn));
    ESP_ERROR_CHECK(iot_button_register_cb(gpio0_btn, BUTTON_SINGLE_CLICK, NULL, gpio0_single_click_cb, NULL));
#endif
}

/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * Scan onboard I2C (SDA=GPIO19, SCL=GPIO20).
 * GT911 is usually 0x5D (default) or 0x14.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "bsp/bsp_uedx80480043_wb_a.h"

static const char *TAG = "i2c_scan";

static void gt911_wakeup_reset(void)
{
    if (BSP_LCD_TOUCH_RST == GPIO_NUM_NC) {
        return;
    }

    gpio_config_t io = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << BSP_LCD_TOUCH_RST,
    };
    gpio_config(&io);
    gpio_set_level(BSP_LCD_TOUCH_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(20));
    gpio_set_level(BSP_LCD_TOUCH_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(80));
}

void app_main(void)
{
    ESP_LOGI(TAG, "I2C scan: SDA=%d SCL=%d", BSP_I2C_SDA, BSP_I2C_SCL);
    gt911_wakeup_reset();
    ESP_ERROR_CHECK(bsp_i2c_init());

    i2c_master_bus_handle_t bus = bsp_i2c_get_handle();
    int found = 0;

    printf("\n     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
    for (int addr = 0; addr < 128; addr++) {
        if ((addr % 16) == 0) {
            printf("%02x: ", addr);
        }

        if (addr == 0) {
            printf("   ");
        } else if (i2c_master_probe(bus, addr, 50) == ESP_OK) {
            printf("%02x ", addr);
            found++;
            ESP_LOGI(TAG, "found device at 0x%02X", addr);
        } else {
            printf("-- ");
        }

        if ((addr % 16) == 15) {
            printf("\n");
        }
    }

    ESP_LOGI(TAG, "scan done, %d device(s). GT911 expected 0x5D or 0x14", found);
}

/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * SPI SD 卡读写测试。引脚：MOSI=11 MISO=13 SCLK=12 CS=10
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "esp_log.h"
#include "bsp/bsp_uedx80480043_wb_a.h"

static const char *TAG = "sd";

static void list_dir(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir) {
        ESP_LOGE(TAG, "opendir %s failed", path);
        return;
    }

    ESP_LOGI(TAG, "listing %s", path);
    struct dirent *ent;
    int count = 0;
    while ((ent = readdir(dir)) != NULL) {
        char full[384];
        snprintf(full, sizeof(full), "%s/%s", path, ent->d_name);
        struct stat st = {0};
        if (stat(full, &st) == 0) {
            ESP_LOGI(TAG, "  %s  %ld bytes%s", ent->d_name, (long)st.st_size,
                     S_ISDIR(st.st_mode) ? " [dir]" : "");
        } else {
            ESP_LOGI(TAG, "  %s", ent->d_name);
        }
        count++;
    }
    closedir(dir);
    ESP_LOGI(TAG, "%d entries", count);
}

void app_main(void)
{
    ESP_LOGI(TAG, "SD SPI example  MOSI=%d MISO=%d SCLK=%d CS=%d",
             BSP_SD_SPI_MOSI, BSP_SD_SPI_MISO, BSP_SD_SPI_SCLK, BSP_SD_SPI_CS);

    esp_err_t ret = bsp_sdcard_mount();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "mount failed: %s", esp_err_to_name(ret));
        return;
    }

    list_dir(BSP_SD_MOUNT_POINT);

    char path[64];
    snprintf(path, sizeof(path), "%s/bsp_sd_test.txt", BSP_SD_MOUNT_POINT);
    FILE *f = fopen(path, "w");
    if (!f) {
        ESP_LOGE(TAG, "create %s failed", path);
        return;
    }
    fprintf(f, "UEDX80480043 SD test OK\n");
    fclose(f);
    ESP_LOGI(TAG, "wrote %s", path);

    char line[64] = {0};
    f = fopen(path, "r");
    if (f) {
        if (fgets(line, sizeof(line), f)) {
            ESP_LOGI(TAG, "read back: %s", line);
        }
        fclose(f);
    }

    ESP_LOGI(TAG, "SD test done");
}

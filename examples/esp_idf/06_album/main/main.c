/*
 * SPDX-FileCopyrightText: 2026 VIEWESMART / VIEWE
 * SPDX-License-Identifier: Apache-2.0
 *
 * Photo album: load jpg/png/bmp from SD and show full-screen with LVGL.
 * Tap left half for previous, right half / BOOT for next.
 */

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "bsp/bsp_uedx80480043_wb_a.h"

static const char *TAG = "album";

#define ALBUM_MAX_FILES          64
#define ALBUM_NAME_MAX           160
#define ALBUM_LVGL_PREFIX        "S:"

static char s_files[ALBUM_MAX_FILES][ALBUM_NAME_MAX];
static int s_file_count;
static int s_index;
static lv_obj_t *s_img;
static lv_obj_t *s_label;
static lv_timer_t *s_timer;

static bool is_image_name(const char *name)
{
    const char *dot = strrchr(name, '.');
    if (!dot || dot == name) {
        return false;
    }
    char ext[8] = {0};
    size_t n = strlen(dot);
    if (n >= sizeof(ext)) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        ext[i] = (char)tolower((unsigned char)dot[i]);
    }
    return strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 ||
           strcmp(ext, ".png") == 0 || strcmp(ext, ".bmp") == 0;
}

static int scan_dir(const char *abs_dir, const char *rel_prefix)
{
    DIR *dir = opendir(abs_dir);
    if (!dir) {
        return 0;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL && s_file_count < ALBUM_MAX_FILES) {
        if (ent->d_name[0] == '.') {
            continue;
        }
        if (!is_image_name(ent->d_name)) {
            continue;
        }

        if (rel_prefix && rel_prefix[0]) {
            snprintf(s_files[s_file_count], ALBUM_NAME_MAX, "%.64s/%.80s", rel_prefix, ent->d_name);
        } else {
            snprintf(s_files[s_file_count], ALBUM_NAME_MAX, "%.150s", ent->d_name);
        }
        s_file_count++;
    }
    closedir(dir);
    return s_file_count;
}

static void scan_images(void)
{
    s_file_count = 0;
    char abs[192];

    if (CONFIG_EXAMPLE_ALBUM_DIR[0] != '\0') {
        snprintf(abs, sizeof(abs), "%s/%.80s", BSP_SD_MOUNT_POINT, CONFIG_EXAMPLE_ALBUM_DIR);
        scan_dir(abs, CONFIG_EXAMPLE_ALBUM_DIR);
        ESP_LOGI(TAG, "scanned %s -> %d image(s)", abs, s_file_count);
    }

    if (s_file_count == 0) {
        scan_dir(BSP_SD_MOUNT_POINT, "");
        ESP_LOGI(TAG, "scanned SD root -> %d image(s)", s_file_count);
    }
}

static void show_current(void)
{
    if (!s_img) {
        return;
    }

    if (s_file_count <= 0) {
        lv_obj_add_flag(s_img, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(s_label, "No images\nPut jpg/png/bmp in /album or SD root");
        lv_obj_center(s_label);
        return;
    }

    if (s_index < 0) {
        s_index = s_file_count - 1;
    }
    if (s_index >= s_file_count) {
        s_index = 0;
    }

    char src[ALBUM_NAME_MAX + 8];
    snprintf(src, sizeof(src), ALBUM_LVGL_PREFIX "%.150s", s_files[s_index]);
    ESP_LOGI(TAG, "show [%d/%d] %s", s_index + 1, s_file_count, src);

    lv_obj_remove_flag(s_img, LV_OBJ_FLAG_HIDDEN);
    lv_image_set_src(s_img, NULL);
    lv_image_set_src(s_img, src);
    lv_obj_set_size(s_img, BSP_LCD_H_RES, BSP_LCD_V_RES);
    lv_image_set_inner_align(s_img, LV_IMAGE_ALIGN_CONTAIN);
    lv_obj_center(s_img);

    char caption[200];
    snprintf(caption, sizeof(caption), "%d / %d  %s", s_index + 1, s_file_count, s_files[s_index]);
    lv_label_set_text(s_label, caption);
    lv_obj_align(s_label, LV_ALIGN_BOTTOM_MID, 0, -8);
}

static void show_current_async(void *user_data)
{
    (void)user_data;
    show_current();
}

/* Decode JPEG/PNG on the LVGL task (32KB stack), never on main/button. */
static void request_show(void)
{
    lv_async_call(show_current_async, NULL);
}

static void album_next(int delta)
{
    if (s_file_count <= 0) {
        return;
    }
    s_index += delta;
    request_show();
}

static void on_screen_click(lv_event_t *e)
{
    lv_point_t p = {0};
    lv_indev_t *indev = lv_event_get_indev(e);
    if (indev) {
        lv_indev_get_point(indev, &p);
    }
    album_next(p.x < (BSP_LCD_H_RES / 2) ? -1 : 1);
}

static void on_slide_timer(lv_timer_t *timer)
{
    (void)timer;
    album_next(1);
}

static void on_boot_click(void *button_handle, void *usr_data)
{
    (void)button_handle;
    (void)usr_data;
    if (bsp_display_lock(-1)) {
        album_next(1);
        bsp_display_unlock();
    }
}

static void ui_create(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_add_flag(scr, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(scr, on_screen_click, LV_EVENT_CLICKED, NULL);

    s_img = lv_image_create(scr);
    lv_obj_center(s_img);

    s_label = lv_label_create(scr);
    lv_obj_set_style_text_color(s_label, lv_color_white(), 0);
    lv_obj_set_style_bg_color(s_label, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(s_label, LV_OPA_50, 0);
    lv_obj_set_style_pad_all(s_label, 6, 0);

    request_show();

#if CONFIG_EXAMPLE_ALBUM_INTERVAL_MS > 0
    if (s_file_count > 1) {
        s_timer = lv_timer_create(on_slide_timer, CONFIG_EXAMPLE_ALBUM_INTERVAL_MS, NULL);
        (void)s_timer;
    }
#endif
}

void app_main(void)
{
    ESP_LOGI(TAG, "electronic album");

    esp_err_t ret = bsp_sdcard_mount();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SD mount failed: %s", esp_err_to_name(ret));
    } else {
        scan_images();
    }

    if (bsp_display_start() == NULL) {
        ESP_LOGE(TAG, "display start failed");
        return;
    }

    if (bsp_display_lock(-1)) {
        ui_create();
        bsp_display_unlock();
    }

    button_handle_t boot = NULL;
    const button_config_t btn_cfg = {0};
    const button_gpio_config_t gpio_cfg = {
        .gpio_num = BSP_BUTTON_BOOT_IO,
        .active_level = 0,
    };
    if (iot_button_new_gpio_device(&btn_cfg, &gpio_cfg, &boot) == ESP_OK) {
        iot_button_register_cb(boot, BUTTON_SINGLE_CLICK, NULL, on_boot_click, NULL);
    }

    ESP_LOGI(TAG, "%d image(s), tap left/right or BOOT", s_file_count);
}

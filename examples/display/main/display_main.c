/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "bsp/esp-bsp.h"
#include "lvgl.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern void example_lvgl_demo_ui(lv_obj_t *scr);

void app_main(void) {
    esp_lcd_touch_handle_t tp;
    bsp_display_start();

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    bsp_display_brightness_set(10);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    bsp_display_brightness_set(50);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    bsp_display_brightness_set(100);
    bsp_display_backlight_off();

    ESP_LOGI("example", "Display LVGL animation");
    bsp_display_lock(0);
    lv_obj_t *scr = lv_disp_get_scr_act(NULL);
    example_lvgl_demo_ui(scr);

    bsp_display_unlock();
    bsp_display_backlight_on();
    bsp_display_brightness_set(50);
}
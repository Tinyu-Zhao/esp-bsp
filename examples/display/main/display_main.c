#include <stdio.h>
#include "bsp/esp-bsp.h"
#include "lvgl.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* 示例UI函数保持不变 */
extern void example_lvgl_demo_ui(lv_obj_t *scr);

static void event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *label      = lv_event_get_user_data(e);

    switch (code) {
        case LV_EVENT_PRESSED:
            lv_label_set_text(label, "The last button event:\nLV_EVENT_PRESSED");
            break;
        case LV_EVENT_CLICKED:
            lv_label_set_text(label, "The last button event:\nLV_EVENT_CLICKED");
            break;
        case LV_EVENT_LONG_PRESSED:
            lv_label_set_text(label, "The last button event:\nLV_EVENT_LONG_PRESSED");
            break;
        case LV_EVENT_LONG_PRESSED_REPEAT:
            lv_label_set_text(label, "The last button event:\nLV_EVENT_LONG_PRESSED_REPEAT");
            break;
        default:
            break;
    }
}

/**
 * Handle multiple events
 */
void lv_example_event_2(void) {
    lv_obj_t *btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 100, 50);
    lv_obj_center(btn);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click me!");
    lv_obj_center(btn_label);

    lv_obj_t *info_label = lv_label_create(lv_screen_active());
    lv_label_set_text(info_label, "The last button event:\nNone");

    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, info_label);
}

void app_main(void) {
    bsp_display_start();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    bsp_display_brightness_set(10);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    bsp_display_brightness_set(50);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    bsp_display_brightness_set(100);
    bsp_display_backlight_off();

    ESP_LOGI("example", "Starting LVGL UI with touch event handling...");

    bsp_display_lock(0);
    lv_obj_t *scr = lv_disp_get_scr_act(NULL);
    example_lvgl_demo_ui(scr);

    /* 注册触摸事件处理回调 */
    // lv_obj_add_event_cb(scr, touch_event_cb, LV_EVENT_ALL, NULL);

    bsp_display_unlock();
    bsp_display_backlight_on();
    bsp_display_brightness_set(50);

    lv_example_event_2();
}
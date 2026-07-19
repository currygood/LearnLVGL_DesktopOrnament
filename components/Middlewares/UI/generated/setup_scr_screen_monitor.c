/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_monitor(lv_ui *ui)
{
    //Write codes screen_monitor
    ui->screen_monitor = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_monitor, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_monitor, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_monitor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_monitor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_monitor, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_monitor, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_cont_cpu
    ui->screen_monitor_cont_cpu = lv_obj_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_cont_cpu, 16, 24);
    lv_obj_set_size(ui->screen_monitor_cont_cpu, 120, 100);
    lv_obj_set_scrollbar_mode(ui->screen_monitor_cont_cpu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(ui->screen_monitor_cont_cpu, LV_OBJ_FLAG_FLOATING);
    lv_obj_remove_flag(ui->screen_monitor_cont_cpu, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for screen_monitor_cont_cpu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_cont_cpu, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_monitor_cont_cpu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_monitor_cont_cpu, lv_color_hex(0xa4a4a4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_monitor_cont_cpu, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_cont_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_cont_cpu, 229, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_monitor_cont_cpu, lv_color_hex(0xff002d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_monitor_cont_cpu, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_cont_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_cont_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_cont_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_cont_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_cont_cpu, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_monitor_cont_cpu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_monitor_cont_cpu, 156, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_monitor_cont_cpu, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_monitor_cont_cpu, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_monitor_cont_cpu, 3, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_img_cpu
    ui->screen_monitor_img_cpu = lv_image_create(ui->screen_monitor_cont_cpu);
    lv_obj_set_pos(ui->screen_monitor_img_cpu, 85, -6);
    lv_obj_set_size(ui->screen_monitor_img_cpu, 40, 41);
    lv_obj_add_flag(ui->screen_monitor_img_cpu, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_monitor_img_cpu, &_cpu_RGB565A8_40x41);
    lv_image_set_pivot(ui->screen_monitor_img_cpu, 50,50);
    lv_image_set_rotation(ui->screen_monitor_img_cpu, 0);

    //Write style for screen_monitor_img_cpu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_monitor_img_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_monitor_img_cpu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_cpu_title
    ui->screen_monitor_label_cpu_title = lv_label_create(ui->screen_monitor_cont_cpu);
    lv_obj_set_pos(ui->screen_monitor_label_cpu_title, 0, 0);
    lv_obj_set_size(ui->screen_monitor_label_cpu_title, 70, 37);
    lv_label_set_text(ui->screen_monitor_label_cpu_title, "CPU");
    lv_label_set_long_mode(ui->screen_monitor_label_cpu_title, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_cpu_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_cpu_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_cpu_title, &lv_font_ZiTiQuanWeiJunHeiW22_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_cpu_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_cpu_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_cpu_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_cpu_useagerate
    ui->screen_monitor_label_cpu_useagerate = lv_label_create(ui->screen_monitor_cont_cpu);
    lv_obj_set_pos(ui->screen_monitor_label_cpu_useagerate, 1, 48);
    lv_obj_set_size(ui->screen_monitor_label_cpu_useagerate, 64, 20);
    lv_label_set_text(ui->screen_monitor_label_cpu_useagerate, "使用率：");
    lv_label_set_long_mode(ui->screen_monitor_label_cpu_useagerate, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_cpu_useagerate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_cpu_useagerate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_cpu_useagerate, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_cpu_useagerate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_cpu_useagerate, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_cpu_useagerate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_cpu_temperature
    ui->screen_monitor_label_cpu_temperature = lv_label_create(ui->screen_monitor_cont_cpu);
    lv_obj_set_pos(ui->screen_monitor_label_cpu_temperature, 1, 75);
    lv_obj_set_size(ui->screen_monitor_label_cpu_temperature, 49, 18);
    lv_label_set_text(ui->screen_monitor_label_cpu_temperature, "温度：");
    lv_label_set_long_mode(ui->screen_monitor_label_cpu_temperature, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_cpu_temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_cpu_temperature, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_cpu_temperature, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_cpu_temperature, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_cpu_temperature, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_cpu_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_cpu_usage_value
    ui->screen_monitor_label_cpu_usage_value = lv_label_create(ui->screen_monitor_cont_cpu);
    lv_obj_set_pos(ui->screen_monitor_label_cpu_usage_value, 70, 47);
    lv_obj_set_size(ui->screen_monitor_label_cpu_usage_value, 64, 20);
    lv_label_set_text(ui->screen_monitor_label_cpu_usage_value, "60%");
    lv_label_set_long_mode(ui->screen_monitor_label_cpu_usage_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_cpu_usage_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_cpu_usage_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_cpu_usage_value, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_cpu_usage_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_cpu_usage_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_cpu_usage_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_cpu_temp_value
    ui->screen_monitor_label_cpu_temp_value = lv_label_create(ui->screen_monitor_cont_cpu);
    lv_obj_set_pos(ui->screen_monitor_label_cpu_temp_value, 70, 76);
    lv_obj_set_size(ui->screen_monitor_label_cpu_temp_value, 64, 20);
    lv_label_set_text(ui->screen_monitor_label_cpu_temp_value, "50℃");
    lv_label_set_long_mode(ui->screen_monitor_label_cpu_temp_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_cpu_temp_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_cpu_temp_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_cpu_temp_value, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_cpu_temp_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_cpu_temp_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_cpu_temp_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_cont_memory
    ui->screen_monitor_cont_memory = lv_obj_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_cont_memory, 178, 24);
    lv_obj_set_size(ui->screen_monitor_cont_memory, 120, 100);
    lv_obj_set_scrollbar_mode(ui->screen_monitor_cont_memory, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(ui->screen_monitor_cont_memory, LV_OBJ_FLAG_FLOATING);
    lv_obj_remove_flag(ui->screen_monitor_cont_memory, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for screen_monitor_cont_memory, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_cont_memory, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_monitor_cont_memory, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_monitor_cont_memory, lv_color_hex(0x7b7b7b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_monitor_cont_memory, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_cont_memory, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_cont_memory, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_monitor_cont_memory, lv_color_hex(0x8cdca4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_monitor_cont_memory, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_cont_memory, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_cont_memory, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_cont_memory, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_cont_memory, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_cont_memory, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_monitor_cont_memory, lv_color_hex(0xe2ffe5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_monitor_cont_memory, 184, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_monitor_cont_memory, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_monitor_cont_memory, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_monitor_cont_memory, 3, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_mem_use_value
    ui->screen_monitor_label_mem_use_value = lv_label_create(ui->screen_monitor_cont_memory);
    lv_obj_set_pos(ui->screen_monitor_label_mem_use_value, 87, 45);
    lv_obj_set_size(ui->screen_monitor_label_mem_use_value, 33, 16);
    lv_label_set_text(ui->screen_monitor_label_mem_use_value, "70%");
    lv_label_set_long_mode(ui->screen_monitor_label_mem_use_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_mem_use_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_mem_use_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_mem_use_value, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_mem_use_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_mem_use_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_mem_use_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_mem_title
    ui->screen_monitor_label_mem_title = lv_label_create(ui->screen_monitor_cont_memory);
    lv_obj_set_pos(ui->screen_monitor_label_mem_title, -7, 0);
    lv_obj_set_size(ui->screen_monitor_label_mem_title, 86, 38);
    lv_label_set_text(ui->screen_monitor_label_mem_title, "内存");
    lv_label_set_long_mode(ui->screen_monitor_label_mem_title, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_mem_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_mem_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_mem_title, &lv_font_ZiTiQuanWeiJunHeiW22_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_mem_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_mem_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_mem_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_img_mem
    ui->screen_monitor_img_mem = lv_image_create(ui->screen_monitor_cont_memory);
    lv_obj_set_pos(ui->screen_monitor_img_mem, 82, -1);
    lv_obj_set_size(ui->screen_monitor_img_mem, 37, 27);
    lv_obj_add_flag(ui->screen_monitor_img_mem, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_monitor_img_mem, &_Memory_Module_RGB565A8_37x27);
    lv_image_set_pivot(ui->screen_monitor_img_mem, 50,50);
    lv_image_set_rotation(ui->screen_monitor_img_mem, 0);

    //Write style for screen_monitor_img_mem, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_monitor_img_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_monitor_img_mem, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_mem_userate
    ui->screen_monitor_label_mem_userate = lv_label_create(ui->screen_monitor_cont_memory);
    lv_obj_set_pos(ui->screen_monitor_label_mem_userate, 2, 46);
    lv_obj_set_size(ui->screen_monitor_label_mem_userate, 62, 21);
    lv_label_set_text(ui->screen_monitor_label_mem_userate, "使用率：");
    lv_label_set_long_mode(ui->screen_monitor_label_mem_userate, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_mem_userate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_mem_userate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_mem_userate, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_mem_userate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_mem_userate, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_mem_userate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_mem_useful
    ui->screen_monitor_label_mem_useful = lv_label_create(ui->screen_monitor_cont_memory);
    lv_obj_set_pos(ui->screen_monitor_label_mem_useful, 0, 75);
    lv_obj_set_size(ui->screen_monitor_label_mem_useful, 46, 16);
    lv_label_set_text(ui->screen_monitor_label_mem_useful, "可用：");
    lv_label_set_long_mode(ui->screen_monitor_label_mem_useful, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_mem_useful, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_mem_useful, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_mem_useful, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_mem_useful, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_mem_useful, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_mem_useful, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_mem_useful_value
    ui->screen_monitor_label_mem_useful_value = lv_label_create(ui->screen_monitor_cont_memory);
    lv_obj_set_pos(ui->screen_monitor_label_mem_useful_value, 86, 75);
    lv_obj_set_size(ui->screen_monitor_label_mem_useful_value, 34, 14);
    lv_label_set_text(ui->screen_monitor_label_mem_useful_value, "5GB");
    lv_label_set_long_mode(ui->screen_monitor_label_mem_useful_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_mem_useful_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_mem_useful_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_mem_useful_value, &lv_font_ZiTiQuanWeiJunHeiW22_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_mem_useful_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_mem_useful_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_mem_useful_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_ta_ip
    ui->screen_monitor_ta_ip = lv_textarea_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_ta_ip, 69, 151);
    lv_obj_set_size(ui->screen_monitor_ta_ip, 166, 31);
    lv_textarea_set_text(ui->screen_monitor_ta_ip, "192.168.4.4");
    lv_textarea_set_placeholder_text(ui->screen_monitor_ta_ip, "");
    lv_textarea_set_password_bullet(ui->screen_monitor_ta_ip, "*");
    lv_textarea_set_password_mode(ui->screen_monitor_ta_ip, false);
    lv_textarea_set_one_line(ui->screen_monitor_ta_ip, false);
    lv_textarea_set_accepted_chars(ui->screen_monitor_ta_ip, "");
    lv_textarea_set_max_length(ui->screen_monitor_ta_ip, 32);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->screen_monitor_ta_ip, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for screen_monitor_ta_ip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_monitor_ta_ip, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_ta_ip, &lv_customer_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_ta_ip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_ta_ip, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_ta_ip, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_ta_ip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_monitor_ta_ip, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_monitor_ta_ip, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_monitor_ta_ip, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_monitor_ta_ip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_monitor_ta_ip, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_monitor_ta_ip, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_ta_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_ta_ip, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_ta_ip, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_ta_ip, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_ta_ip, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_monitor_ta_ip, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_monitor_ta_ip, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_monitor_ta_ip, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_monitor_ta_ip, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_ta_ip, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_monitor_btn_connect
    ui->screen_monitor_btn_connect = lv_button_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_btn_connect, 244, 151);
    lv_obj_set_size(ui->screen_monitor_btn_connect, 55, 30);
    ui->screen_monitor_btn_connect_label = lv_label_create(ui->screen_monitor_btn_connect);
    lv_label_set_text(ui->screen_monitor_btn_connect_label, "连接");
    lv_label_set_long_mode(ui->screen_monitor_btn_connect_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_monitor_btn_connect_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_monitor_btn_connect, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_monitor_btn_connect_label, LV_PCT(100));

    //Write style for screen_monitor_btn_connect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_monitor_btn_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_monitor_btn_connect, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_monitor_btn_connect, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_monitor_btn_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_btn_connect, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_btn_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_btn_connect, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_btn_connect, &lv_customer_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_btn_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_btn_connect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_cp
    ui->screen_monitor_label_cp = lv_label_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_label_cp, 16, 156);
    lv_obj_set_size(ui->screen_monitor_label_cp, 53, 19);
    lv_label_set_text(ui->screen_monitor_label_cp, "主机：");
    lv_label_set_long_mode(ui->screen_monitor_label_cp, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_cp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_cp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_cp, &lv_customer_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_cp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_cp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_cp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_constate_value
    ui->screen_monitor_label_constate_value = lv_label_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_label_constate_value, 193, 196);
    lv_obj_set_size(ui->screen_monitor_label_constate_value, 75, 30);
    lv_label_set_text(ui->screen_monitor_label_constate_value, "未连接");
    lv_label_set_long_mode(ui->screen_monitor_label_constate_value, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_constate_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_constate_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_constate_value, &lv_customer_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_constate_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_constate_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_constate_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_label_constate
    ui->screen_monitor_label_constate = lv_label_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_label_constate, 102, 196);
    lv_obj_set_size(ui->screen_monitor_label_constate, 94, 20);
    lv_label_set_text(ui->screen_monitor_label_constate, "连接状态：");
    lv_label_set_long_mode(ui->screen_monitor_label_constate, LV_LABEL_LONG_WRAP);

    //Write style for screen_monitor_label_constate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_monitor_label_constate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_monitor_label_constate, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_monitor_label_constate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_monitor_label_constate, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_monitor_label_constate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_monitor_img_constate
    ui->screen_monitor_img_constate = lv_image_create(ui->screen_monitor);
    lv_obj_set_pos(ui->screen_monitor_img_constate, 43, 175);
    lv_obj_set_size(ui->screen_monitor_img_constate, 52, 38);
    lv_obj_add_flag(ui->screen_monitor_img_constate, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_monitor_img_constate, &_connect_state_RGB565A8_52x38);
    lv_image_set_pivot(ui->screen_monitor_img_constate, 50,50);
    lv_image_set_rotation(ui->screen_monitor_img_constate, -240);

    //Write style for screen_monitor_img_constate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_monitor_img_constate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor(ui->screen_monitor_img_constate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_monitor_img_constate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_monitor.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_monitor);

    //Init events for screen.
    events_init_screen_monitor(ui);
}

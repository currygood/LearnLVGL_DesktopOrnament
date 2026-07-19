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




int screen_home_click_now_min_value = 25;
int screen_home_click_now_hour_value = 11;
int screen_home_click_now_sec_value = 50;
void setup_scr_screen_home(lv_ui *ui)
{
    //Write codes screen_home
    ui->screen_home = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_home, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_home, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(ui->screen_home, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for screen_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_click_now
    static bool screen_home_click_now_timer_enabled = false;
    ui->screen_home_click_now = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_click_now, -17, 46);
    lv_obj_set_size(ui->screen_home_click_now, 210, 52);
    lv_label_set_text(ui->screen_home_click_now, "11:25:50");
    if (!screen_home_click_now_timer_enabled) {
        lv_timer_create(screen_home_click_now_timer, 1000, NULL);
        screen_home_click_now_timer_enabled = true;
    }

    //Write style for screen_home_click_now, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_click_now, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_click_now, &lv_font_ZiTiQuanWeiJunHeiW22_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_click_now, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_click_now, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_click_now, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_click_now, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_lable_date
    ui->screen_home_lable_date = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_lable_date, 174, 46);
    lv_obj_set_size(ui->screen_home_lable_date, 119, 20);
    lv_label_set_text(ui->screen_home_lable_date, "2026-7-16");
    lv_label_set_long_mode(ui->screen_home_lable_date, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_lable_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_lable_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_lable_date, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_lable_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_lable_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_lable_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_lable_week
    ui->screen_home_lable_week = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_lable_week, 239, 76);
    lv_obj_set_size(ui->screen_home_lable_week, 57, 17);
    lv_label_set_text(ui->screen_home_lable_week, "星期三");
    lv_label_set_long_mode(ui->screen_home_lable_week, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_lable_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_lable_week, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_lable_week, &lv_customer_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_lable_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_lable_week, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_lable_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_lable_location
    ui->screen_home_lable_location = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_lable_location, 200, 9);
    lv_obj_set_size(ui->screen_home_lable_location, 179, 41);
    lv_label_set_text(ui->screen_home_lable_location, "未知");
    lv_label_set_long_mode(ui->screen_home_lable_location, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_lable_location, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_lable_location, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_lable_location, &lv_customer_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_lable_location, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_lable_location, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_lable_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_today
    ui->screen_home_label_today = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_today, 26, 118);
    lv_obj_set_size(ui->screen_home_label_today, 52, 25);
    lv_label_set_text(ui->screen_home_label_today, "今天");
    lv_label_set_long_mode(ui->screen_home_label_today, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_today, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_today, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_today, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_today, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_today, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_tomorrow
    ui->screen_home_label_tomorrow = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_tomorrow, 122, 118);
    lv_obj_set_size(ui->screen_home_label_tomorrow, 52, 25);
    lv_label_set_text(ui->screen_home_label_tomorrow, "明天");
    lv_label_set_long_mode(ui->screen_home_label_tomorrow, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_tomorrow, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_tomorrow, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_tomorrow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_afterday
    ui->screen_home_label_afterday = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_afterday, 218, 118);
    lv_obj_set_size(ui->screen_home_label_afterday, 52, 25);
    lv_label_set_text(ui->screen_home_label_afterday, "后天");
    lv_label_set_long_mode(ui->screen_home_label_afterday, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_afterday, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_afterday, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_afterday, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_afterday, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_afterday, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_todaywehter
    ui->screen_home_label_todaywehter = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_todaywehter, -8, 213);
    lv_obj_set_size(ui->screen_home_label_todaywehter, 114, 37);
    lv_label_set_text(ui->screen_home_label_todaywehter, "28-32℃");
    lv_label_set_long_mode(ui->screen_home_label_todaywehter, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_todaywehter, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_todaywehter, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_todaywehter, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_todaywehter, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_todaywehter, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_todaywehter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_tomorrowwether
    ui->screen_home_label_tomorrowwether = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_tomorrowwether, 85, 213);
    lv_obj_set_size(ui->screen_home_label_tomorrowwether, 123, 37);
    lv_label_set_text(ui->screen_home_label_tomorrowwether, "27-33℃");
    lv_label_set_long_mode(ui->screen_home_label_tomorrowwether, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_tomorrowwether, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_tomorrowwether, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_tomorrowwether, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_tomorrowwether, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_tomorrowwether, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_tomorrowwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_label_afterwether
    ui->screen_home_label_afterwether = lv_label_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_label_afterwether, 191, 213);
    lv_obj_set_size(ui->screen_home_label_afterwether, 111, 36);
    lv_label_set_text(ui->screen_home_label_afterwether, "25-30℃");
    lv_label_set_long_mode(ui->screen_home_label_afterwether, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_label_afterwether, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_label_afterwether, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_label_afterwether, &lv_font_ZiTiQuanWeiJunHeiW22_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_label_afterwether, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_label_afterwether, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_label_afterwether, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_wifi
    ui->screen_home_img_wifi = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_wifi, 0, -2);
    lv_obj_set_size(ui->screen_home_img_wifi, 37, 41);
    lv_obj_add_flag(ui->screen_home_img_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_wifi, &_wifi_RGB565A8_37x41);
    lv_image_set_pivot(ui->screen_home_img_wifi, 50,50);
    lv_image_set_rotation(ui->screen_home_img_wifi, 0);
	lv_obj_add_flag(ui->screen_home_img_wifi, LV_OBJ_FLAG_HIDDEN);	// 初始化不显示wifi，连接上后显示

    //Write style for screen_home_img_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_slice
    ui->screen_home_img_slice = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_slice, 12, 97);
    lv_obj_set_size(ui->screen_home_img_slice, 302, 19);
    lv_obj_add_flag(ui->screen_home_img_slice, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_slice, &_line_RGB565A8_302x19);
    lv_image_set_pivot(ui->screen_home_img_slice, 50,50);
    lv_image_set_rotation(ui->screen_home_img_slice, 0);

    //Write style for screen_home_img_slice, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_slice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_slice, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_today
    ui->screen_home_img_today = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_today, 23, 146);
    lv_obj_set_size(ui->screen_home_img_today, 46, 51);
    lv_obj_add_flag(ui->screen_home_img_today, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_today, &_yun_RGB565A8_46x51);
    lv_image_set_pivot(ui->screen_home_img_today, 50,50);
    lv_image_set_rotation(ui->screen_home_img_today, 0);

    //Write style for screen_home_img_today, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_today, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_tomorrow
    ui->screen_home_img_tomorrow = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_tomorrow, 122, 146);
    lv_obj_set_size(ui->screen_home_img_tomorrow, 46, 51);
    lv_obj_add_flag(ui->screen_home_img_tomorrow, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_tomorrow, &_qing_RGB565A8_46x51);
    lv_image_set_pivot(ui->screen_home_img_tomorrow, 50,50);
    lv_image_set_rotation(ui->screen_home_img_tomorrow, 0);

    //Write style for screen_home_img_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_img_afterday
    ui->screen_home_img_afterday = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_img_afterday, 218, 146);
    lv_obj_set_size(ui->screen_home_img_afterday, 46, 51);
    lv_obj_add_flag(ui->screen_home_img_afterday, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_home_img_afterday, &_yu_RGB565A8_46x51);
    lv_image_set_pivot(ui->screen_home_img_afterday, 50,50);
    lv_image_set_rotation(ui->screen_home_img_afterday, 0);

    //Write style for screen_home_img_afterday, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_img_afterday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_img_afterday, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_home.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_home);

    //Init events for screen.
    events_init_screen_home(ui);
}

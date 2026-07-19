/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>


__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
#if LV_USE_KEYBOARD
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        if(lv_indev_get_type(lv_indev_active()) != LV_INDEV_TYPE_KEYPAD) {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
        }
    } else if(code == LV_EVENT_READY) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);
    } else if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
#endif
}

void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
		if(*min == 60)
        {
            *min = 0;
            (*hour)++;
			if(*hour == 24)
			{
				*hour = 0;
			}
		}
    }
}

void digital_clock_count(int * hour, int * minute, int * seconds, char * meridiem)
{

    (*seconds)++;
    if(*seconds == 60) {
        *seconds = 0;
        (*minute)++;
		if(*minute == 60)
        {
            *minute = 0;
            (*hour)++;
			if(*hour == 24)
			{
				*hour = 0;
			}
		}
    }
}


extern int screen_home_click_now_hour_value;
extern int screen_home_click_now_min_value;
extern int screen_home_click_now_sec_value;

extern int screen_home_click_now_year_value;
extern int screen_home_click_now_month_value;
extern int screen_home_click_now_day_value;
extern int screen_home_click_now_week_value;

void date_count(void)
{
	static const char *week_day_text[]={
		"星期天",
		"星期一",
		"星期二",
		"星期三",
		"星期四",
		"星期五",
		"星期六",
	};

    time_t now = time(NULL);
	struct tm t;
	localtime_r(&now,&t);
	screen_home_click_now_year_value = t.tm_year + 1900;
	screen_home_click_now_month_value = t.tm_mon + 1;
	screen_home_click_now_day_value = t.tm_mday;
	screen_home_click_now_week_value = t.tm_wday;

	char strTemp[64];
	snprintf(strTemp,sizeof strTemp,"%d-%02d-%02d",screen_home_click_now_year_value,
		screen_home_click_now_month_value,
		screen_home_click_now_day_value);

	lv_label_set_text(guider_ui.screen_home_lable_date,strTemp);
	lv_label_set_text(guider_ui.screen_home_lable_week,week_day_text[screen_home_click_now_week_value]);
}

void screen_home_click_now_timer(lv_timer_t *timer)
{
    clock_count(&screen_home_click_now_hour_value, &screen_home_click_now_min_value, &screen_home_click_now_sec_value);
    
	if(screen_home_click_now_sec_value == 0 && screen_home_click_now_min_value == 0 && screen_home_click_now_hour_value == 0)
	{
		date_count();
	}

	if (lv_obj_is_valid(guider_ui.screen_home_click_now))
    {
        lv_label_set_text_fmt(guider_ui.screen_home_click_now, "%d:%02d:%02d", screen_home_click_now_hour_value, screen_home_click_now_min_value, screen_home_click_now_sec_value);
    }
}


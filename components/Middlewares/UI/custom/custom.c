/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lvgl.h"
#include "custom.h"
#include "esp_lvgl_port.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

extern int screen_home_click_now_hour_value;
extern int screen_home_click_now_min_value;
extern int screen_home_click_now_sec_value;

int screen_home_click_now_year_value;
int screen_home_click_now_month_value;
int screen_home_click_now_day_value;
int screen_home_click_now_week_value;

void set_home_time(lv_ui *ui,int year,int month,int day,int hour,int min,int sec,int week_value)
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

    screen_home_click_now_year_value = year;
    screen_home_click_now_month_value = month;
    screen_home_click_now_day_value = day;
    screen_home_click_now_hour_value = hour;
    screen_home_click_now_min_value = min;
    screen_home_click_now_sec_value = sec;
    screen_home_click_now_week_value = week_value;

	char strTemp[64];
	snprintf(strTemp,sizeof strTemp,"%d-%02d-%02d",year,month,day);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_home_lable_date,strTemp);
	lv_label_set_text(ui->screen_home_lable_week,week_day_text[week_value]);
	lvgl_port_unlock();
}

void set_today_weather(lv_ui *ui,char *img_path,int low_temp,int high_temp)
{
	char tempStr[32];
	snprintf(tempStr,sizeof tempStr,"%d℃-%d℃",low_temp,high_temp);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_home_label_todaywehter,tempStr);
	lv_img_set_src(ui->screen_home_img_today,img_path);
	lvgl_port_unlock();
}

void set_tomorrow_weather(lv_ui *ui,char *img_path,int low_temp,int high_temp)
{
	char tempStr[32];
	snprintf(tempStr,sizeof tempStr,"%d℃-%d℃",low_temp,high_temp);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_home_label_tomorrowwether,tempStr);
	lv_img_set_src(ui->screen_home_img_tomorrow,img_path);
	lvgl_port_unlock();
}

void set_afterTomorrow_weather(lv_ui *ui,char *img_path,int low_temp,int high_temp)
{
	char tempStr[32];
	snprintf(tempStr,sizeof tempStr,"%d℃-%d℃",low_temp,high_temp);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_home_label_afterwether,tempStr);
	lv_img_set_src(ui->screen_home_img_afterday,img_path);
	lvgl_port_unlock();
}

void set_city_name(lv_ui *ui,char *city_name)
{
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_home_lable_location,city_name);
	lvgl_port_unlock();
}

void set_wifi_visible(lv_ui *ui,bool visible)
{
	lvgl_port_lock(0);
	if(visible)
		lv_obj_remove_flag(ui->screen_home_img_wifi, LV_OBJ_FLAG_HIDDEN);
	else
		lv_obj_add_flag(ui->screen_home_img_wifi, LV_OBJ_FLAG_HIDDEN);
	lvgl_port_unlock();
}

void set_monitor_params(lv_ui *ui,int cpu_rate,int cpu_temp,int mem_rate,int mem_useful)
{
	char value[16];
	// cpu rate
	snprintf(value,sizeof value,"%d%%",cpu_rate);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_monitor_label_cpu_usage_value,value);
	lvgl_port_unlock();

	// cpu temp
	snprintf(value,sizeof value,"%d℃",cpu_temp);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_monitor_label_cpu_temp_value,value);
	lvgl_port_unlock();

	// mem rate
	snprintf(value,sizeof value,"%d%%",mem_rate);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_monitor_label_mem_use_value,value);
	lvgl_port_unlock();

	// mem useful
	snprintf(value,sizeof value,"%dG",mem_useful);
	lvgl_port_lock(0);
	lv_label_set_text(ui->screen_monitor_label_mem_useful_value,value);
	lvgl_port_unlock();
}

void set_monitor_status(lv_ui *ui,bool connected)
{
	lvgl_port_lock(0);
	if(connected)
	{
		lv_label_set_text(ui->screen_monitor_label_constate_value,"已连接");
		lv_label_set_text(ui->screen_monitor_btn_connect_label,"断开");
	}
	else
	{
		lv_label_set_text(ui->screen_monitor_label_constate_value,"未连接");
		lv_label_set_text(ui->screen_monitor_btn_connect_label,"连接");
	}
	lvgl_port_unlock();
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}


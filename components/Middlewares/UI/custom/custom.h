/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "AIDA64.h"


void custom_init(lv_ui *ui);
// 设置首页时间
void set_home_time(lv_ui *ui,int year,int month,int day,int hour,int min,int sec,int week_value);
// 设置首页今天天气
void set_today_weather(lv_ui *ui,char *img_path,int low_temp,int high_temp);
// 设置首页明天天气
void set_tomorrow_weather(lv_ui *ui,char *img_path,int low_temp,int high_temp);
// 设置首页后天天气
void set_afterTomorrow_weather(lv_ui *ui,char *img_path,int low_temp,int high_temp);
// 设置首页城市名称
void set_city_name(lv_ui *ui,char *city_name);
// 设置wifi是否显示
void set_wifi_visible(lv_ui *ui,bool visible);
// 设置电脑连接状态
void set_monitor_status(lv_ui *ui,bool connected);
// 设置硬件参数
void set_monitor_params(lv_ui *ui,int cpu_rate,int cpu_temp,int mem_rate,int mem_useful);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */

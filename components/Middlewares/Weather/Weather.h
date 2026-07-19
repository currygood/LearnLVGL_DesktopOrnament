#ifndef __WEATHER_H__
#define __WEATHER_H__

typedef struct Weather_Data_Struct
{
	float high_tempature;
	float low_tempature;
	char code[4];
}Weather_Data_Str;


void weather_start();

#endif

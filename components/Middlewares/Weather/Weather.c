#include "Weather.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "custom.h"

#define TAG "Weather"
#define WEATHER_BUFFER_SIZE 2048
#define WEATHER_API_KEY "ST5xPj7PH5DmWPuT6"

static uint8_t Weather_Data_Buffer[WEATHER_BUFFER_SIZE];// http接收到的数据
static int Weather_Data_Size = 0; // 接收到的数据大小
static char Weather_Location_City[64] = {0};

static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
	switch(evt->event_id)
	{
		case HTTP_EVENT_ERROR:

			break;
		case HTTP_EVENT_ON_CONNECTED:

			break;
		case HTTP_EVENT_HEADER_SENT:

			break;
		case HTTP_EVENT_ON_HEADER:

			break;
		case HTTP_EVENT_ON_DATA:
			int copy_len = 0;
			if(evt->data_len > WEATHER_BUFFER_SIZE - Weather_Data_Size)
				copy_len = WEATHER_BUFFER_SIZE - Weather_Data_Size;
			else
				copy_len = evt->data_len;

			memcpy(Weather_Data_Buffer + Weather_Data_Size, evt->data, copy_len);
			Weather_Data_Size += copy_len;

			break;
		case HTTP_EVENT_ON_FINISH:

			break;
		case HTTP_EVENT_DISCONNECTED:

			break;
		case HTTP_EVENT_REDIRECT:

			break;

		default:
			break;
	}
	return ESP_OK;
}

static esp_err_t Weather_HTTP_Parse_Data(char *js)
{
	Weather_Data_Str weather_data[3];
	char city_name[64];
	int index=0;


	if(Weather_Data_Size <= 0)
	{
		ESP_LOGE(TAG, "No data received");
		return ESP_FAIL;
	}

	js[Weather_Data_Size] = '\0';

	ESP_LOGI(TAG, "Received data (%d bytes): %s", Weather_Data_Size, js);

	cJSON *root = cJSON_Parse(js);
	if(root == NULL)
	{
		ESP_LOGE(TAG, "cJSON_Parse failed");
		return ESP_FAIL;
	}

	cJSON *result_js = cJSON_GetObjectItem(root, "results");
	if(result_js == NULL)
	{
		ESP_LOGE(TAG, "cJSON_GetObjectItem failed");
		return ESP_FAIL;
	}

	cJSON *result_child_js = result_js->child;
	if(result_child_js == NULL)
	{
		ESP_LOGE(TAG, "cJSON_GetObjectItem failed");
		return ESP_FAIL;
	}

	cJSON *location_js = cJSON_GetObjectItem(result_child_js, "location");
	cJSON *city_name_js = cJSON_GetObjectItem(location_js, "name");
	if(city_name_js)
	{
		snprintf(city_name,sizeof city_name,"%s",cJSON_GetStringValue(city_name_js));
	}

	cJSON *daily_js = cJSON_GetObjectItem(result_child_js, "daily");
	if(daily_js == NULL)
	{
		ESP_LOGE(TAG, "cJSON_GetObjectItem failed");
		return ESP_FAIL;
	}

	cJSON *daily_child_js = daily_js->child;
	while(daily_child_js != NULL)
	{
		cJSON *hightempature_js = cJSON_GetObjectItem(daily_child_js, "high");
		cJSON *lowtempature_js = cJSON_GetObjectItem(daily_child_js, "low");
		cJSON *code_js = cJSON_GetObjectItem(daily_child_js, "code_day");
		sscanf(cJSON_GetStringValue(hightempature_js),"%f",&weather_data[index].high_tempature);
		sscanf(cJSON_GetStringValue(lowtempature_js),"%f",&weather_data[index].low_tempature);
		snprintf(weather_data[index].code,sizeof weather_data[index].code,"%s",cJSON_GetStringValue(code_js));

		// 打印测试
		ESP_LOGI(TAG, "day:%d index high_tempature: %f, low_tempature: %f, code: %s",index,weather_data[index].high_tempature,weather_data[index].low_tempature,weather_data[index].code);

		index++;
		if(index == 3)
		{
			break;
		}
		daily_child_js = daily_child_js->next;
	}
	// 设置数据到显示界面
	char img_path[256];

	memset(img_path, 0, sizeof img_path);
	snprintf(img_path,sizeof img_path,"S:%s@1x.png",weather_data[0].code);
	set_today_weather(&guider_ui,img_path,(int)weather_data[0].low_tempature,(int)weather_data[0].high_tempature);

	memset(img_path, 0, sizeof img_path);
	snprintf(img_path,sizeof img_path,"S:%s@1x.png",weather_data[1].code);
	set_tomorrow_weather(&guider_ui,img_path,(int)weather_data[1].low_tempature,(int)weather_data[1].high_tempature);

	memset(img_path, 0, sizeof img_path);
	snprintf(img_path,sizeof img_path,"S:%s@1x.png",weather_data[2].code);
	set_afterTomorrow_weather(&guider_ui,img_path,(int)weather_data[2].low_tempature,(int)weather_data[2].high_tempature);

	// 设置城市名称
	set_city_name(&guider_ui,city_name);

	cJSON_Delete(root);
	return ESP_OK;
}

static esp_err_t Weather_HTTP_Connect()
{
	esp_err_t err;
	static char url[256];
	memset(url, 0, 256);

	snprintf(url,sizeof url,"http://api.seniverse.com/v3/weather/daily.json?key=%s&location=%s&language=zh-Hans&unit=c&start=0&days=3",WEATHER_API_KEY,Weather_Location_City);

	ESP_LOGI(TAG, "Weather URL: %s", url);

	esp_http_client_config_t config = {
		.url = url,
		.event_handler = http_event_handler,
	};

	esp_http_client_handle_t http_client = esp_http_client_init(&config);
	memset(Weather_Data_Buffer, 0, WEATHER_BUFFER_SIZE);
	Weather_Data_Size = 0;

	err = esp_http_client_perform(http_client);

	if(err == ESP_OK)
	{
		int status_code = esp_http_client_get_status_code(http_client);
		ESP_LOGI(TAG, "HTTP Status Code: %d", status_code);

		if(status_code == 200)
		{
			if(Weather_Data_Size > 0)
			{
				err = Weather_HTTP_Parse_Data((char *)Weather_Data_Buffer);
			}
			else
			{
				ESP_LOGE(TAG, "No data received");
				err = ESP_FAIL;
			}
		}
		else
		{
			ESP_LOGE(TAG, "HTTP request failed with status: %d", status_code);
			err = ESP_FAIL;
		}
	}
	else
	{
		ESP_LOGE(TAG, "HTTP perform failed: %s", esp_err_to_name(err));
	}

	esp_http_client_cleanup(http_client);

	return err;
}

static esp_err_t Weather_HTTP_Parse_Location_Data(char *js)
{
	/*{"ip":"113.74.211.2","pro":"广东省","proCode":"440000","city":"清远市","cityCode":"441800","region":"","regionCode":"0","addr":"广东省清远市 电信","regionNames":"","err":""}*/
	cJSON *location_js = cJSON_Parse(js);
	if(location_js == NULL)
	{
		ESP_LOGE(TAG, "cJSON_Parse failed");
		return ESP_FAIL;
	}

	cJSON *city_js = cJSON_GetObjectItem(location_js, "city");
	if(city_js == NULL)
	{
		ESP_LOGE(TAG, "cJSON_GetObjectItem failed");
		return ESP_FAIL;
	}
	snprintf(Weather_Location_City,sizeof Weather_Location_City,"%s",cJSON_GetStringValue(city_js));

	cJSON_Delete(location_js);
	return ESP_OK;
}

static esp_err_t Weather_GetLocation_HTTP_Connect()
{
	esp_err_t err; 
	static char url[256];
	memset(url, 0, 256);

	snprintf(url,sizeof url,"http://ip-api.com/json/?lang=en");

	esp_http_client_config_t config = {
		.url = url,
		.event_handler = http_event_handler,
	};

	esp_http_client_handle_t http_client = esp_http_client_init(&config);
	memset(Weather_Data_Buffer, 0, WEATHER_BUFFER_SIZE);
	Weather_Data_Size = 0;

	err = esp_http_client_perform(http_client);

	Weather_HTTP_Parse_Location_Data((char *)Weather_Data_Buffer);

	esp_http_client_cleanup(http_client);

	return err;
}

static void weather_task(void *pvParameters)
{
	while(!Wifi_Is_Connected())
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	Weather_GetLocation_HTTP_Connect();
	Weather_HTTP_Connect();

	vTaskDelete(NULL);
}

void weather_start()
{
	xTaskCreatePinnedToCore(weather_task, "weather_task", 4096, NULL, 2, NULL, 0);
}
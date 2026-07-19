#include "AIDA64.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "custom.h"
#include "cJSON.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define TAG "AIDA64"
#define AIDA64_EVENT_CONNECTED_BIT (1 << 0)

static TaskHandle_t AIDA64_Monitor_Task_Handle = NULL;
static char aida64server_url[128] = {0};
static esp_http_client_handle_t AIDA64_http_client = NULL;
static EventGroupHandle_t AIDA64_Event_Group = NULL;
static bool AIDA64_is_connected = false;
AIDA64_Parse_Data_t latest_data;
extern lv_ui guider_ui;

static bool AIDA64_Monitor_Parse_BYAIDA(char *data, size_t len, AIDA64_Parse_Data_t *parse_data)
{
    if (data == NULL || parse_data == NULL || len == 0) {
        return false;
    }

    // 确保数据以 "data:" 开头 (SSE 标准)
    char *p_start = strstr(data, "data:");
    if (!p_start) {
        return false;
    }

    // 提取 CPU 使用率
    char *p_cpu_rate = strstr(p_start, "CPU_Rate");
    if (p_cpu_rate) {
        // sscanf 会跳过非数字字符，直接提取整数
        sscanf(p_cpu_rate, "CPU_Rate %d", &parse_data->cpu_rate);
    }

    // 提取 CPU 温度
    char *p_cpu_temp = strstr(p_start, "CPU_Temp");
    if (p_cpu_temp) {
        sscanf(p_cpu_temp, "CPU_Temp %d", &parse_data->cpu_temp);
    }

    // 提取 内存使用率
    char *p_mem_rate = strstr(p_start, "Mem_Rate");
    if (p_mem_rate) {
        sscanf(p_mem_rate, "Mem_Rate %d", &parse_data->mem_rate);
    }

    // 提取 内存使用量 (单位 MB)
    char *p_mem_use = strstr(p_start, "Mem_Use");
    if (p_mem_use) {
        sscanf(p_mem_use, "Mem_Use %d", &parse_data->mem_useful);
    }

    return true;
}

static bool AIDA64_Monitor_Parse_MyApp(char *data, size_t len, AIDA64_Parse_Data_t *parse_data)
{
    if (data == NULL || parse_data == NULL || len == 0) {
        return false;
    }

    char *pStart = strstr(data, "data:");
    if (!pStart) {
        return false;
    }
    pStart += 5;

    cJSON *root = cJSON_Parse(pStart);
    if (!root) {
        return false;
    }

    cJSON *hardParams = cJSON_GetObjectItem(root, "HardParams");
    if (!hardParams || !cJSON_IsArray(hardParams)) {
        cJSON_Delete(root);
        return false;
    }

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, hardParams)
    {
        cJSON *child = item->child;
        if (!child) {
            continue;
        }

        const char *key = child->string;
        if (key == NULL) {
            continue;
        }

        if (strcmp(key, "cpu_cpu_package_wmi_avg_temperature") == 0) {
            parse_data->cpu_temp = (int)round(child->valuedouble);
        }
        else if (strcmp(key, "memory_memory_load") == 0) {
            parse_data->mem_rate = (int)round(child->valuedouble);
        }
        else if (strcmp(key, "cpu_cpu_total_load") == 0) {
            parse_data->cpu_rate = (int)round(child->valuedouble);
        }
        else if (strcmp(key, "memory_memory_available_data") == 0) {
            parse_data->mem_useful = (int)round(child->valuedouble);
        }
    }

    cJSON_Delete(root);
    return true;
}

static esp_err_t AIDA64_http_event_handler(esp_http_client_event_t *evt)
{
	switch(evt->event_id)
	{
		case HTTP_EVENT_ERROR:
			
			break;
		case HTTP_EVENT_ON_CONNECTED:
			AIDA64_is_connected = true;

			break;
		case HTTP_EVENT_HEADER_SENT:

			break;
		case HTTP_EVENT_ON_HEADER:

			break;
		case HTTP_EVENT_ON_DATA:
			if (evt->data_len > 0) {
                // 1. 临时分配空间并确保以 \0 结尾，方便字符串操作
                char *buffer = (char *)malloc(evt->data_len + 1);
                if (buffer) {
                    memcpy(buffer, evt->data, evt->data_len);
                    buffer[evt->data_len] = '\0';

                    // 2. 调用解析函数
                    if (AIDA64_Monitor_Parse_MyApp(buffer, evt->data_len, &latest_data)) {
                        ESP_LOGI(TAG, "Parsed: CPU:%d%%, Temp:%d°C, Mem:%d%%, %dGB", 
                                 latest_data.cpu_rate, latest_data.cpu_temp, 
                                 latest_data.mem_rate, latest_data.mem_useful);
                        set_monitor_params(&guider_ui,latest_data.cpu_rate,latest_data.cpu_temp,
                            latest_data.mem_rate,latest_data.mem_useful);
                        set_monitor_status(&guider_ui,AIDA64_is_connected?true:false);
                    }
                    free(buffer);

					
                }
            }

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

static void AIDA64_Monitor_Task(void *pvParameters)
{
	(void)pvParameters;
	static EventBits_t event_bits = 0;
	esp_http_client_config_t config = {
		.url = aida64server_url,
		.event_handler = AIDA64_http_event_handler,
	};

	AIDA64_http_client = esp_http_client_init(&config);
	
	while(1)
	{
		event_bits = xEventGroupWaitBits(AIDA64_Event_Group, AIDA64_EVENT_CONNECTED_BIT, true, false, portMAX_DELAY);
		if(event_bits & AIDA64_EVENT_CONNECTED_BIT)
		{
			// 设置url地址
			esp_http_client_set_url(AIDA64_http_client, aida64server_url);
			esp_http_client_set_method(AIDA64_http_client, HTTP_METHOD_GET);
			esp_http_client_set_header(AIDA64_http_client, "Accept", "text/event-stream");
			ESP_LOGI(TAG, "AIDA64_Monitor_Task: %s", aida64server_url);
			esp_http_client_perform(AIDA64_http_client);
			AIDA64_is_connected = false;	// 当断开连接，前一个函数就会返回了，然后就执行到这里，设置标志位为false
		}
		
	}
}

/**
 * @brief 启动AIDA64监控
 * 
 * @param ip AIDA64服务器IP地址
*/
void AIDA64_Monitor_Start(const char *ip,int port)
{
	// 下面这个是AIDA64的监控端口
	// snprintf(aida64server_url, sizeof(aida64server_url), "http://%s:80/sse", ip);
	// 这是我自己开发的监控端口
	snprintf(aida64server_url, sizeof(aida64server_url), "http://%s:%d/api/stream", ip,port);
	if(!AIDA64_Event_Group)
		AIDA64_Event_Group = xEventGroupCreate();
	if(!AIDA64_Monitor_Task_Handle)
		xTaskCreatePinnedToCore(AIDA64_Monitor_Task, "AIDA64_Monitor_Task", 4096, NULL, 3, &AIDA64_Monitor_Task_Handle, 0);
	xEventGroupSetBits(AIDA64_Event_Group, AIDA64_EVENT_CONNECTED_BIT);
}

/**
 * @brief 获取AIDA64监控状态
 * 
 * @return true 监控已启动
 * @return false 监控未启动
*/
bool AIDA64_Monitor_Get_Status()
{
	if(AIDA64_is_connected)
		return true;
	return false;
}

/**
 * @brief 停止AIDA64监控
 * 
*/
void AIDA64_Monitor_Stop()
{
	esp_http_client_close(AIDA64_http_client);
}
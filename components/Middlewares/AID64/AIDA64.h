#ifndef __AIDA64_H__
#define __AIDA64_H__

#include <stdbool.h>

#define MYAPP_MONITOR_PORT 5000

typedef struct AIDA64_Parse_Data
{
	int cpu_rate;
	int cpu_temp;
	int mem_rate;
	int mem_useful;
}AIDA64_Parse_Data_t;

// 启动AIDA64监控
void AIDA64_Monitor_Start(const char *ip,int port);

// 获取AIDA64监控状态
bool AIDA64_Monitor_Get_Status();

// 停止AIDA64监控
void AIDA64_Monitor_Stop();



#endif

#ifndef __DEVICECOMMON_H__
#define __DEVICECOMMON_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include "stdio.h"

typedef int deviceNotifyMsg;
	
typedef enum{
	KEY_EVENT=1,
	EVENT_MAX
}EVENT_T;

typedef struct deviceNotification{
		EVENT_T type;
		int len;
		void* msg;
}deviceNotification;

typedef struct{
	unsigned short id;
	unsigned short action;
	unsigned short value;
}Commom_msg_t;


#ifdef __cplusplus
}
#endif


#endif //__DEVICECOMMON_H__

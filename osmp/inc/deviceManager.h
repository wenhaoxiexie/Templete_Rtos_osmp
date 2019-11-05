#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__

#ifdef __cplusplus
extern "C"
{
#endif

// include 
#include "deviceCommon.h"
	
//server 
typedef struct serviceList_t{
		struct serviceList_t* next;
		void (*serviceActive)(struct serviceList_t* var);
		void (*serviceDeactive)(struct serviceList_t* var);
		void (*deviceNotified)(deviceNotification* evt);
}serviceList_t;
	
	
typedef struct deviceManagerList_t deviceManagerList_t;

//controll
typedef struct controllList_t{
		struct controllList_t* next;
		void (*controllActive)(deviceManagerList_t* dev);
		void (*controllDeactive)(deviceManagerList_t* dev);
}controllList_t;

//deviceManager
typedef struct deviceManagerList_t{
		serviceList_t* sHead;
		controllList_t* cHead;
		void (*addService)(deviceManagerList_t* dev,serviceList_t* ser);
		void (*addControll)(deviceManagerList_t* dev,controllList_t* con);
		void (*serviceActive)(deviceManagerList_t* dev);
		void (*serviceDeactive)(deviceManagerList_t* dev);
		void (*controllActive)(deviceManagerList_t* dev);
		void (*conrollDeactive)(deviceManagerList_t* dev);
		void (*notifyService)(deviceManagerList_t* dev,EVENT_T type,void* msg,int len);
}deviceManagerList_t;


void notifyService(deviceManagerList_t* dev,EVENT_T type,void* msg,int len);

deviceManagerList_t * deviceManager_init(void);
#ifdef __cplusplus
}
#endif

#endif //__DEVICEMANAGER_H__


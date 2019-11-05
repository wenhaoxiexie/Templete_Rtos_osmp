#include "deviceManager.h"
#include "stdlib.h"


static void addService(deviceManagerList_t* dev,serviceList_t* ser)
{
	if(dev==NULL||ser==NULL)
		return ;
	
	serviceList_t** pTemp=&(dev->sHead);
	while(*pTemp!=NULL)
	{
		pTemp=&((*pTemp)->next);
	}
	*pTemp=ser;
}

static void addControll(deviceManagerList_t* dev,controllList_t* con)
{
	if(dev==NULL||con==NULL)
		return ;
	controllList_t** pTemp=&(dev->cHead);
	while(*pTemp!=NULL)
	{
		pTemp=&((*pTemp)->next);
	}
	*pTemp=con;
}

static void serviceActiveList(deviceManagerList_t* dev)
{
	if(dev==NULL)
		return ;
	
	serviceList_t* pTemp=dev->sHead;
	while(pTemp!=NULL)
	{
		pTemp->serviceActive(pTemp);
		pTemp=pTemp->next;
	}
}

static void serviceDeactiveList(deviceManagerList_t* dev)
{
	if(dev==NULL)
		return ;
	serviceList_t* pTemp=dev->sHead;
	while(pTemp!=NULL)
	{
		pTemp->serviceDeactive(pTemp);
		pTemp=pTemp->next;
	}
}

static void controllActiveList(deviceManagerList_t* dev)
{
	if(dev==NULL)
		return ;
	controllList_t* pTemp=dev->cHead;
	while(pTemp!=NULL)
	{
		pTemp->controllActive(dev);
		pTemp=pTemp->next;
	}
}

static void controllDeactiveList(deviceManagerList_t* dev)
{
	if(dev==NULL)
		return ;
	controllList_t* pTemp=dev->cHead;
	while(pTemp!=NULL)
	{
		pTemp->controllDeactive(dev);
		pTemp=pTemp->next;
	}
}

void notifyService(deviceManagerList_t* dev,EVENT_T type,void* msg,int len)
{
	if(dev==NULL)
		return ;
	deviceNotification note;
	note.type=type;
	note.msg=msg;
	note.len=len;
	
	serviceList_t *pTemp=dev->sHead;
	while(pTemp!=NULL)
	{
		if(	pTemp->deviceNotified)
		{
				pTemp->deviceNotified(&note);
		}
		pTemp=pTemp->next;
	}
}

deviceManagerList_t* deviceManager_init()
{
	deviceManagerList_t *dev=(deviceManagerList_t*)calloc(1,sizeof(deviceManagerList_t)); 
	
	dev->addService=addService;
	dev->addControll=addControll;
	dev->serviceActive=serviceActiveList;
	dev->serviceDeactive=serviceDeactiveList;
	dev->controllActive=controllActiveList;
	dev->conrollDeactive=controllDeactiveList;
	dev->notifyService=notifyService;
	
	return dev;
}


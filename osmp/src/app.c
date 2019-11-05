#include "stdlib.h"
#include "app.h"
#include "usart.h"

static void controllActive(deviceManagerList_t* con)
{
	printf(" enter controllActive function \r\n");
}

static void controllDeactive(deviceManagerList_t* con)
{
	printf(" enter controllDeactive function \r\n");
}

controllList_t* app_controll_create()
{
	controllList_t* app=(controllList_t*)calloc(1,sizeof(controllList_t));
	
	app->controllActive=controllActive;
	app->controllDeactive=controllDeactive;
	return app;
}

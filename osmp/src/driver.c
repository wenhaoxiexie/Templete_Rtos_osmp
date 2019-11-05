#include "stdlib.h"
#include "driver.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//�������ȼ�
#define TASK_TASK_PRIO		2
//�����ջ��С	
#define TASK_STK_SIZE 		128  
//������
static TaskHandle_t Task_Handler;

//������Ϣ���е�����
#define MESSAGE_Q_NUM   4   	//�������ݵ���Ϣ���е����� 
static QueueHandle_t Message_Queue=NULL;	//��Ϣ���о��

static void driver_service_notified(deviceNotification* evt)
{
	Commom_msg_t msg={0};
	
	deviceNotifyMsg data =*(deviceNotifyMsg*)(evt->msg);
	if(evt->type==KEY_EVENT)
	{
		msg.id=evt->type;
		msg.action=data;
		
		if(msg.id!=0)
		{
			xQueueSend(Message_Queue,&msg,0);
		}
	}
}

//������
void task_task(void *pvParameters)
{
	int count=0;
	Commom_msg_t msg={0};
	
	while(1)
	{
		printf(" count��%d \r\n",count);
		if(xQueueReceive(Message_Queue,&msg,portMAX_DELAY))
		{
			printf(" recived msg %d\r\n",msg.action);
		}
		printf(" count��%d \r\n",count);
		count++;
		vTaskDelay(1000); 
	}
}

static void driver_service_active(serviceList_t* var)
{
		printf(" enter driver_service_active function \r\n");
		//������Ϣ����
		Message_Queue=xQueueCreate(MESSAGE_Q_NUM,sizeof(Commom_msg_t)); //������ϢMessage_Queue,��������Ǵ��ڽ��ջ���������
	
		taskENTER_CRITICAL();           //�����ٽ���
    //����TASK����
    xTaskCreate((TaskFunction_t )task_task,             
                (const char*    )"task_task",           
                (uint16_t       )TASK_STK_SIZE,        
                (void*          )var,                  
                (UBaseType_t    )TASK_TASK_PRIO,        
                (TaskHandle_t*  )&Task_Handler);   
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

static void driver_service_deactive(serviceList_t* var)
{
		printf(" enter driver_service_deactive function \r\n");
		
		//vTaskDelete(Task_Handler); //ɾ����ʼ����
		
		printf(" delete task Task_Handler \r\n");

}

serviceList_t* driver_service_create(void)
{
	serviceList_t *driver = (serviceList_t*)calloc(1,sizeof(serviceList_t));
	if(driver)
	{
		driver->serviceActive=driver_service_active;
		driver->serviceDeactive=driver_service_deactive;
		driver->deviceNotified=driver_service_notified;
	}
	return driver;
}	

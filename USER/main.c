#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "deviceManager.h"
#include "driver.h"
#include "app.h"
#include "sleep.h"

static void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
	
  SystemClock_Config();
	
	usart1_init();
		
	// 登记服务和控制函数
	deviceManagerList_t *dev = deviceManager_init();

	serviceList_t *driver=driver_service_create();
	dev->addService(dev,driver);
	
	controllList_t *app=app_controll_create();
	dev->addControll(dev,app);
	
	//运行注册列表
	dev->serviceActive(dev);
	dev->serviceDeactive(dev);
	
	dev->controllActive(dev);
	dev->conrollDeactive(dev);
	int num=10;
	dev->notifyService(dev,KEY_EVENT,&num,4);
	num++;
	dev->notifyService(dev,KEY_EVENT,&num,4);
	num++;
	dev->notifyService(dev,KEY_EVENT,&num,4);
	num++;
	dev->notifyService(dev,KEY_EVENT,&num,4);
	num++;
	dev->notifyService(dev,KEY_EVENT,&num,4);
	num++;
	dev->notifyService(dev,KEY_EVENT,&num,4);
	
	// 延时测试
	printf(" delay start\r\n");
	delay_s(5);
	printf(" delay end\r\n");
	
	//开启任务调度
	vTaskStartScheduler();        

}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    while(1);
  }
}


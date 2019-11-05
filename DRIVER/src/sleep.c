#include "sleep.h"

// 自定义延时函数
static void sleep(uint32_t time)
{
	for(;time!=0;time--);
}

// 1us 延时函数
void delay_us(uint32_t delay)
{
	while(delay--)
		sleep(20);
}

// 1ms 延时函数

void delay_ms(uint32_t delay)
{
	while(delay--)
		sleep(20*1000);
}

// 1s 延时函数

void delay_s(uint32_t delay)
{
	while(delay--)
		sleep(20*1000*1000);
}


#include "sleep.h"

// �Զ�����ʱ����
static void sleep(uint32_t time)
{
	for(;time!=0;time--);
}

// 1us ��ʱ����
void delay_us(uint32_t delay)
{
	while(delay--)
		sleep(20);
}

// 1ms ��ʱ����

void delay_ms(uint32_t delay)
{
	while(delay--)
		sleep(20*1000);
}

// 1s ��ʱ����

void delay_s(uint32_t delay)
{
	while(delay--)
		sleep(20*1000*1000);
}


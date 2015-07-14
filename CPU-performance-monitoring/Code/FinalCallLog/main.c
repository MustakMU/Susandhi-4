#include "structureDefine.h"
#include <stm32l1xx.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_rtc.h>
#include <stm32l1xx_pwr.h>
#include <stm32l1xx_usart.h>
#include<stm32l1xx_gpio.h>
#include <misc.h>
#include <string.h>
char gUartRxDataBuffer[40];
int checkContactOrLog=0,uartDataAvailable=0;
int countContact=0,sleepControl=0;
int countCallLog=0;
int duration[2];
char *previousCommand="";
char *array[9]={"cmd","dis","cr","del","ed","clog","load","cpu","mc"};
//int mainRange[2];
RTC_TimeTypeDef RTC_TimeStruct;
char *loopRange[2];
extern unsigned long _idle;
extern unsigned long _eidle;

int mainLoop() __attribute__ ((section(".idle")));
int mainLoop()
{
	while(1)
	{
		if(uartDataAvailable==1)
		{
			parsing((char*)gUartRxDataBuffer,headContact,headCallLog);
			uartDataAvailable=0;
		}
	}
}
int main(void)
{
   	UartInit(9600);
	SystemCoreClockUpdate();
	SystemCoreClock=2097152;
	SysTick_Config(SystemCoreClock/1000);
	headContact=malloc(sizeof(LinkPtr));
	headCallLog=malloc(sizeof(LinkPtr));
	createList(headContact);
	createList(headCallLog);
	gpioInit();
	realTimeClockInit();
	queueInit();
	loopRange[0]=(char *)mainLoop;
	loopRange[1]=(char *)&_eidle;
	mainLoop();
	return 0;
}

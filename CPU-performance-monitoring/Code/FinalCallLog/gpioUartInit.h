#ifndef __GPIOUARTINIT_H
#define __GPIOUARTINIT_H

#include <stm32l1xx.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_rtc.h>
#include <stm32l1xx_pwr.h>
#include<stm32l1xx_usart.h>
#include<stm32l1xx_gpio.h>
#include <misc.h>
#include <string.h>
#include "structureDefine.h"

void gpioInit();
void setLedBlink();
void resetLedBlink();
void  UartPrint(char* outStr);
void  UartInit(uint32_t baudRate);
void  UartPrint(char* outStr);
uint16_t UartRead(void);
int UartLoopBack(void);
void realTimeClockInit(void);
void secondsCalculate(callLogPtr_t nodeLog);
int parsing(char *string,LinkPtr headContact,LinkPtr headCallLog);

#endif

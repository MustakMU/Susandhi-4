
/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_dma.h"

void DMA_memcpy( const uint32_t *, uint32_t*, uint32_t) ;
void initGPIO(void);
void blinkLED();
int globalVar1,globalVar2,globalVar3,globalVar4;
extern unsigned long _ebss,_sbss;

 void DMA_memcpy(const uint32_t *src_address, uint32_t *dest_address, uint32_t sizeInWords) {
/* DMA1 channel6 configuration ---------------------------------------------*/

	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel6);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)dest_address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)src_address;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = sizeInWords;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel6, ENABLE);
	while ( DMA_GetFlagStatus( DMA1_FLAG_TC6) == RESET) ;
}

int main()
{
	const uint32_t sourceVar=0;
	uint32_t bufferSize;
	bufferSize=(&_ebss - &_sbss);
	initGPIO();
	DMA_memcpy(&sourceVar,&_sbss,bufferSize);
	globalVar1=globalVar2+globalVar3;
	globalVar4=globalVar3+globalVar1;
	if( DMA_GetFlagStatus( DMA1_FLAG_TC6) == SET)
	{
	    blinkLED();
	}
	while(1)
	{

	}
	return 0;
}

void initGPIO(void)
{
	    GPIO_InitTypeDef myGpioStruct;
    	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
    	myGpioStruct.GPIO_Mode =GPIO_Mode_OUT;
    	myGpioStruct.GPIO_OType = GPIO_OType_PP;
    	myGpioStruct.GPIO_Pin= GPIO_Pin_7 | GPIO_Pin_6;
    	myGpioStruct.GPIO_PuPd = GPIO_PuPd_UP;
    	myGpioStruct.GPIO_Speed = GPIO_Speed_40MHz;
    	GPIO_Init(GPIOB,&myGpioStruct);
    	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
void blinkLED()
{
    	GPIO_SetBits(GPIOB,GPIO_Pin_6);
}


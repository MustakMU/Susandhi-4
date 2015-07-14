#include "gpioUartInit.h"

extern char gUartRxDataBuffer[40];
extern int uartDataAvailable;
int countU=0;
void  UartInit(uint32_t baudRate)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* enable clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);


  GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1 );//Tx
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1 );//Rx

  /* config IO pins */
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*config USART */
  USART_StructInit(&USART_InitStruct);
  USART_Init(USART1, &USART_InitStruct);

  /*USART Interrupt config*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /*enable USART*/
  USART_Cmd(USART1, ENABLE);

  /* Enable the USART1 receive interrupt */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

}
void UartPrint(char* outStr)
{
    while(*outStr!='\0')
    {
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
        USART_SendData(USART1,(uint8_t) (*outStr));
        outStr++;
    }
}

uint16_t UartRead(void)
{
    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET) { };
    return (USART_ReceiveData(USART1));
}


int USART1_IRQHandler(void)
{

    /*Got 1 byte of data*/
	if( USART_GetITStatus(USART1, USART_IT_RXNE) )
	{
		/*Store the recevied byte into buffer*/
		gUartRxDataBuffer[countU]=USART1->DR;
		//check for the termination and increase the counter
		USART_SendData(USART1,gUartRxDataBuffer[countU]);
		if(gUartRxDataBuffer[countU++]=='\r')
		{
			gUartRxDataBuffer[--countU]='\0';
			uartDataAvailable=1;
			countU=0;
		}
	}
	return 1;
}

#include <stm32l1xx_gpio.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_usart.h>
#include <stm32l1xx_dma.h>
#include <misc.h>


uint8_t gUartRxDataBuffer[20];
uint8_t recvArray[20];
 uint8_t xmitArray[20] ;
__IO uint32_t xmitEndOfTransfer = 0;
__IO uint32_t recvEndOfTransfer  = 0;

extern int count;
void  UartInit(uint32_t baudRate);
int main(void)
{
	count=0;
    int i=sizeof (xmitArray) ;
    while ((xmitArray[i--] = 'a' +i)  !='a');

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /*enable USART*/
    UartInit(9600) ;
    /* Enable Transfer Complete INterrupt genration in DMA1 */
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
    /* Program the DMA/SRC and destination register */
    DMA_UartXferInit( DMA_DIR_PeripheralDST,xmitArray,sizeof (xmitArray));
    /* Enable USART to send events to DMA, rather then an  interrupt */
    USART_DMACmd (USART1, USART_DMAReq_Tx, ENABLE);

   /* Enable the DMA enginer */
    DMA_Cmd(DMA1_Channel4, ENABLE);
  //  DMA_Cmd(DMA1_Channel5, ENABLE);

    /*  Enable the corresponding NVIC IRQ */
    DMA_NVICXmitSetup() ;

    USART_Cmd(USART1, ENABLE);
    while (DMA_GetITStatus (DMA1_IT_TC4) == RESET) ;
    while(1)
    {

    }
}
void  UartInit(uint32_t baudRate)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
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
  USART_InitStruct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_Parity     = USART_Parity_No;
  USART_InitStruct.USART_BaudRate   = 9600;
  USART_InitStruct.USART_StopBits   = USART_StopBits_1;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStruct);

}

//In order to catch end of DMA transfer we initialized DMA transfer Complete on channel interrupt.
int  DMA_NVICXmitSetup() //Global interrupt Enable
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    return 0 ;
}
int   DMA_UartXferInit( uint32_t dir, unsigned char* dataBuf,
                        uint32_t sizeInBytes)
{
    	DMA_Channel_TypeDef *dmaChannel ;
    	DMA_InitTypeDef DMA_InitStructure ;
    	dmaChannel = DMA1_Channel4 ;

        DMA_DeInit(dmaChannel);
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)& (USART1->DR);
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) dataBuf;
        DMA_InitStructure.DMA_DIR = dir  ;
        DMA_InitStructure.DMA_BufferSize = sizeInBytes;
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
        DMA_InitStructure.DMA_Priority = DMA_Priority_High;
        DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
        DMA_Init(dmaChannel, &DMA_InitStructure);

        return 0 ;
}


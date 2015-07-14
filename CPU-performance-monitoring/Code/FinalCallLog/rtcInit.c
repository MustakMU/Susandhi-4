#include "gpioUartInit.h"

extern uint8_t gUartRxDataBuffer[40];
extern char *previousCommand;
extern int checkContactOrLog;
extern int duration[2];
extern RTC_TimeTypeDef RTC_TimeStruct;

void realTimeClockInit(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);     /// Enable the PWR clock.
		PWR_RTCAccessCmd(ENABLE);                               /// Allow access to RTC.
		RCC_RTCResetCmd(ENABLE);                                /// Reset RTC Domain.
		RCC_RTCResetCmd(DISABLE);

		RCC_LSEConfig(RCC_LSE_ON);                              /// Enable the LSE OSC.
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET){}   /// Wait till LSE is ready.

		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);                 /// Select the RTC Clock Source.

		RTC_InitTypeDef RTC_InitStructure;                      /// Configure the RTC data register and RTC prescaler.
		RTC_InitStructure.RTC_HourFormat    =   RTC_HourFormat_12;
		RTC_InitStructure.RTC_AsynchPrediv  =   0x7F;
		RTC_InitStructure.RTC_SynchPrediv   =   0xFF;
		RTC_Init(&RTC_InitStructure);

		RCC_RTCCLKCmd(ENABLE);                                  /// Enable the RTC Clock.
		RTC_WaitForSynchro();                                   /// Wait for RTC APB registers synchronisation.

		RTC_TimeStruct.RTC_H12 = RTC_H12_AM;
		RTC_TimeStruct.RTC_Hours   = 00;
		RTC_TimeStruct.RTC_Minutes = 00;
		RTC_TimeStruct.RTC_Seconds = 00;
		RTC_SetTime(RTC_Format_BIN,&RTC_TimeStruct);
		RTC_DateTypeDef RTC_DateStruct;
		RTC_DateStructInit(&RTC_DateStruct);

		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;    /// Enable the RTC Wakeup Interrupt.
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		RTC_WakeUpCmd(DISABLE);

		/* Configure the RTC WakeUp Clock source: CK_SPRE (1Hz) */
		RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
		RTC_SetWakeUpCounter(0x0);

		/* Enable the RTC Wakeup Interrupt */
		RTC_ITConfig(RTC_IT_WUT, ENABLE);

		/* Enable Wakeup Counter */
		RTC_WakeUpCmd(ENABLE);

}

void secondsCalculate(callLogPtr_t nodeLog)
{
	int index=0;
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
	duration[checkContactOrLog]=RTC_TimeStruct.RTC_Seconds+(RTC_TimeStruct.RTC_Minutes*60)+(RTC_TimeStruct.RTC_Hours*3600);
	if(checkContactOrLog==0)
	{
		index=getTimeOfCall(RTC_TimeStruct.RTC_Hours,index,nodeLog);
		nodeLog->time[index++]=':';
		index=getTimeOfCall(RTC_TimeStruct.RTC_Minutes,index,nodeLog);
		nodeLog->time[index++]=':';
		index=getTimeOfCall(RTC_TimeStruct.RTC_Seconds,index,nodeLog);
		nodeLog->time[index]='\0';
	}
	return;
}

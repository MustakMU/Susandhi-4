#include "cpuLoad.h"
#include "structureDefine.h"
int idle=0,mSecCount=0;
char cpuLoadBuffer[13][18];
extern int loopRange[2];
char* intToChar(int num,char *stringOut)
{
	int i=0,j=0;
	char tempString[10];
	if(num!=0)
	{
		while(num!=0)
		{
			tempString[i]=num%10+'0';
			num=num/10;
			i++;
		}
		i--;
		while(i>=0)
		{
			stringOut[j]=tempString[i];
			j++;
			i--;
		}
	}
	else
	{
		stringOut[j]='0';
		j++;
	}
	stringOut[j]='\0';
	return stringOut;
}
void dataPush()
{
	float cpuLoad=(1000-idle)*0.1;
	intToChar(cpuLoad,cpuLoadBuffer[myQueue.end]);
	if(isQueueFull(&myQueue)!=1)
	{
		enqQueue(&myQueue,(void *)cpuLoadBuffer[myQueue.end]);
	}
	else
	{
		deqQueue(&myQueue);
		enqQueue(&myQueue,(void *)cpuLoadBuffer[myQueue.end]);
	}

}

LinkPtr cpuLoad(LinkPtr head,LinkPtr headLog)
{
	char *charPtr;
	int loadVal=0,count=0;
	charPtr=strtok(NULL," ");
	while(*charPtr!='\0')
	{
		loadVal=loadVal*10+(*charPtr-'0');
	    charPtr++;
	}
	count=loadVal*2050;
	while(count!=0)
	{
		count--;
	}
	return NULL;
}
LinkPtr getCpuLoad(LinkPtr head,LinkPtr headLog)
{
	int i=0;
	char *str;
	for(i=0;i<10;i++)
	{
		if(isQueueEmpty(&myQueue)!=1)
		{
			str=(char*)deqQueue(&myQueue);
			UartPrint(str);
			UartPrint("\r\n");
		}
	}
	return NULL;
}
void SysTick_Handler(void)
{
	register int volatile temp __asm("sp");
	int *returnVal=(int *)temp;
	if(returnVal[10]>= loopRange[0] && returnVal[10] <=loopRange[1])
	{
		idle++;
	}
	mSecCount++;
	if(mSecCount==1000)
	{
		dataPush();
		mSecCount=0;
		idle=0;
	}

}

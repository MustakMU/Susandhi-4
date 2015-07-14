#include "structureDefine.h"
/*#include "gpioUartInit.h"
#include "compareFunction.h"*/


extern int checkContactOrLog;
extern uint8_t gUartRxDataBuffer[40];
extern int duration[2];
extern int countCallLog;
extern char previousCommand[5];


/*It checks the checkName in contact list if found it returns 0
 * else it returns 1
 */
int cmpNameFxn(LinkPtr node, LinkPtr data)
{
	if(checkContactOrLog==1)
	{
		contactPtr_t temp,temp1;
		temp=(contactPtr_t)node;
		temp1=(contactPtr_t)data;
		return strcmp(temp->name,temp1->name);
	}
	else
	{
		callLogPtr_t temp2,temp3;
		temp2=(callLogPtr_t)node;
		temp3=(callLogPtr_t)data;
		return strcmp(temp2->name,temp3->name);
	}
}
/*It checks the checkNumber in contact list if found it returns 0
 * else it returns 1
 */
int cmpNumberFxn(LinkPtr node, LinkPtr data)
{
	if(checkContactOrLog==1)
	{
		contactPtr_t temp,temp1;
		temp=(contactPtr_t)node;
		temp1=(contactPtr_t)data;
		return strcmp(temp->number,temp1->number);
	}
	else
	{
		callLogPtr_t temp2,temp3;
		temp2=(callLogPtr_t)node;
		temp3=(callLogPtr_t)data;
		return strcmp(temp2->number,temp3->number);
	}
}
checkValue checkNumber(char number[])
{
	int temp=0;
	for(temp=0;number[temp]!='\0';temp++)
	{
		if(number[temp]<48 || number[temp]>57)
		{
			return no;
		}
	}
	temp=strlen(number);
	if(temp!=10)
	{
	   		return no;
	}
	else
	{
		return yes;
	}

}
checkValue checkName(char name[])
{
	int index=0,temp=0;
	for(index=0;name[index]!='\0';index++)
	{
		if(name[index]<48||name[index]>58)
		{
			continue;
		}
		else
		{
			temp++;
		}
	}
	if((temp==10) || (strlen(name)>=10))
	{
		return no;
	}
	else
	{
		return yes;
	}
}
void numToChar(int value,callLogPtr_t nodeLog)
{
	int j=0;
	while(value!=0)
	{
		gUartRxDataBuffer[j]=(value%10)+48;
		value=value/10;
		j++;
	}
	value=0;
	j--;
	while(j>=0)
	{
		nodeLog->duration[value]=gUartRxDataBuffer[j];
		j--;
		value++;
	}
	j=0;
	gUartRxDataBuffer[value]='\0';
	nodeLog->duration[value]='\0';
	return;
}
int getTimeOfCall(int time,int j,callLogPtr_t nodeLog)
{
	char string[20];
	int i=0;
	if(time==0)
	{
		string[i]='0';
		i++;
	}
	while(time!=0)
	{
		string[i]=(time%10)+48;
		time=time/10;
		i++;
	}
	time=0;
	i--;
	while(i>=0)
	{
		nodeLog->time[j]=string[i];
		i--;
		j++;
	}
	return j;
}


#include "structureDefine.h"
extern char gUartRxDataBuffer[40];
extern char *previousCommand;
extern int countContact;
extern int countCallLog;
extern int checkContactOrLog;
extern int duration[2],uartDataAvailable;
#define maximum 9

LinkPtr create(LinkPtr head,LinkPtr headLog)
{
	funRetValue=getNameOrNum(&tempAssignValueContact,head,NULL);
	if(funRetValue==NULL)
	{
		funRetValue=getNameOrNum(&tempAssignValueContact,head,NULL);
		if(funRetValue==NULL)
		{
			if(countContact<maximum)
			{
				contactPtr_t newContact;
				newContact=malloc(sizeof(contactDescriptor));
				if(newContact==NULL)
				{
					UartPrint("\r\nOut of memory\r\n");
					return head;
				}
				strcpy(newContact->name,tempAssignValueContact.name);
				strcpy(newContact->number,tempAssignValueContact.number);
				checkContactOrLog=1;
				sort(head,(LinkPtr)newContact,cmpNameFxn);
				countContact++;
				printingSuccess(2);
				return head;
			}
			else
			{
				printingError(2);
				return NULL;
			}
		}
		else if(funRetValue==head)
		{
			return NULL;
		}
		else
		{
			printingError(3);
			return NULL;
		}
	}
	else if(funRetValue==head)
	{
		return NULL;
	}
	else
	{
		printingError(3);
	}
	return NULL;
}
LinkPtr DeleteContact(LinkPtr head,LinkPtr headLog)
{
	funRetValue=getNameOrNum(&tempAssignValueContact,head,NULL);
	if(funRetValue!=NULL && funRetValue!=head)
	{
		deletion(funRetValue);
		free(funRetValue);
		funRetValue=NULL;
		countContact--;
		printingSuccess(3);
		return head;
	}
	else if(funRetValue==NULL)
	{
		printingError(4);
		return NULL;
	}
	return head;
}
LinkPtr editContact(LinkPtr head,LinkPtr headLog)
{
	LinkPtr tempRet;
	tempRet=getNameOrNum(&tempAssignValueContact,head,NULL);
	if(tempRet==NULL)
	{
		printingError(4);
		return NULL;
	}
	else if(tempRet==head)
	{
		printingError(6);
		return NULL;
	}
	else
	{
		funRetValue=getNameOrNum(&tempAssignValueContact,head,NULL);
		if(funRetValue==tempRet || funRetValue==NULL)
		{
			funRetValue=getNameOrNum(&tempAssignValueContact,head,NULL);
			if(funRetValue==tempRet || funRetValue==NULL)
			{
				contactPtr_t newContact;
				newContact=malloc(sizeof(contactDescriptor));
				if(newContact==NULL)
				{
					UartPrint("\r\nout of memory\r\n");
					return head;
				}
				strcpy(newContact->name,tempAssignValueContact.name);
				strcpy(newContact->number,tempAssignValueContact.number);
				sort((LinkPtr)head,(LinkPtr)newContact,cmpNameFxn);
				deletion(tempRet);
				free(tempRet);
				tempRet=NULL;
				printingSuccess(4);
			}
			else if(funRetValue==head)
			{
				printingError(6);
				return NULL;
			}
			else
			{
				printingError(4);
				return NULL;
			}
		}
		else if(funRetValue==head)
		{
			printingError(6);
			return NULL;
		}
		else
		{
			printingError(4);
			return NULL;
		}
	}
	return head;
}
LinkPtr makecall(LinkPtr head,LinkPtr headLog)
{
	if(countCallLog==maximum)
	{
		checkContactOrLog=0;
		funRetValue=linearsearch(headLog,(LinkPtr)headLog->previousContact,cmpNumberFxn);
		if(funRetValue!=NULL)
		{
			printingError(8);
			deletion(funRetValue);
			free(funRetValue);
			funRetValue=NULL;
		}
	}
	funRetValue=getNameOrNum(NULL,head,&preNodeLog);
	if(funRetValue==head)
	{
		return NULL;
	}
	else if(funRetValue==NULL)
	{
		strcpy(preNodeLog.name,"\0");
	}
	else
	{
		contactPtr_t tempCont=(contactPtr_t)funRetValue;
		strcpy(preNodeLog.number,tempCont->number);
		strcpy(preNodeLog.name,tempCont->name);
	}
	strcpy(preNodeLog.type,"Out");
	setLedBlink();
	checkContactOrLog=0;
	secondsCalculate(&preNodeLog);
	uartDataAvailable=0;
	while(1)
	{
		if(uartDataAvailable==1)
		{
			if(strcmp("ec",gUartRxDataBuffer)==0)
		   	{
		   			endcall(headContact,headCallLog);
		   			uartDataAvailable=0;
		   			break;
		   	}
			else if(strcmp(gUartRxDataBuffer,"cpu")==0)
		   	{
		   		getCpuLoad(headContact,headCallLog);
		   		uartDataAvailable=0;
		   	}
		   	else
		   	{
		   	   	printingError(6);
		   	   	uartDataAvailable=0;
		   	}
		}
	}
	return headLog;
}
LinkPtr endcall(LinkPtr head,LinkPtr headLog)
{
	callLogPtr_t nodeLog;
	nodeLog=malloc(sizeof(callLog));
	if(nodeLog==NULL)
	{
		UartPrint("out of memory\n");
		return head;
	}
	strcpy(nodeLog->name,preNodeLog.name);
	strcpy(nodeLog->number,preNodeLog.number);
	strcpy(nodeLog->type,preNodeLog.type);
	strcpy(nodeLog->time,preNodeLog.time);
	resetLedBlink();
	checkContactOrLog=1;
	secondsCalculate(nodeLog);
	numToChar((duration[1]-duration[0]),nodeLog);
	checkContactOrLog=0;
	funRetValue=linearsearch(headLog,(LinkPtr)nodeLog,cmpNumberFxn);
	if(funRetValue!=NULL)
	{
		deletion(funRetValue);
		free(funRetValue);
		funRetValue=NULL;
		countCallLog--;
	}
	insert(headLog,(LinkPtr)nodeLog);
	printingSuccess(6);
	countCallLog++;
	return headLog;
}




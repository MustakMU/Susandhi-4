#include "display.h"
#include "structureDefine.h"

LinkPtr displayContactList(LinkPtr head,LinkPtr headLog)
{
	UartPrint("\r\n");
	funRetValue=head->nextContact;
	if(funRetValue==head)
	{
		printingError(1);
		return NULL;
	}
	else
	{
		contactPtr_t temp1;
		while(funRetValue!=head)
		{
			temp1=(contactPtr_t)funRetValue;
			UartPrint(temp1->name);
			UartPrint("\t");
			UartPrint(temp1->number);
			UartPrint("\r\n");
			funRetValue=funRetValue->nextContact;
		}
	}
	printingSuccess(1);
	return head;
}
LinkPtr commands(LinkPtr head,LinkPtr headLog)
{
	UartPrint("Different commands offered are as follows: \r\n");
	UartPrint("Use -na to enter the name and -nu to enter number\r\n");
	UartPrint("''dis''					Displays contact list\r\n");
	UartPrint("''cr -na name -nu number''		To create contact list\r\n");
	UartPrint("''cr -nu number -na name''		To create contact list\r\n");
	UartPrint("''del -na name''				To delete contact details\r\n");
	UartPrint("''del -nu number''				To delete contact details\r\n");
	UartPrint("''ed -na existingName -na name -nu -number''	To edit contact details\r\n");
	UartPrint("''ed -na existingNum -na name -nu -number''		 To edit contact details\r\n");
	UartPrint("''clog''					To display calllog details\r\n");
	UartPrint("''mc -nu number''			To make a call\r\n");
	UartPrint("''mc -na name''				To make a call\r\n");
	UartPrint("''ec''			To end the call\r\n");
	return head;
}
LinkPtr displayCallLog(LinkPtr head,LinkPtr headLog)
{
	funRetValue=headLog->nextContact;
	UartPrint("\r\n");
	if(funRetValue==headLog)
	{
		printingError(5);
		return NULL;
	}
	else
	{
		callLogPtr_t temp1;
		while(funRetValue!=headLog)
		{
			temp1=(callLogPtr_t)funRetValue;
			UartPrint(temp1->number);
			UartPrint("\t");
			if(temp1->name[0]!='\0')
			{
				UartPrint(temp1->name);
				UartPrint("\t");
			}
			else
			{
				UartPrint("\t\t");
			}
			UartPrint(temp1->type);
			UartPrint("\ttime:");
			UartPrint(temp1->time);
			UartPrint("\tdur:");
			UartPrint(temp1->duration);
			UartPrint("sec\r\n");
			funRetValue=funRetValue->nextContact;
		}
	}
	printingSuccess(5);
	return headLog;
}
void printingError(int tempRet)
{
	switch(tempRet)
	{
		case 1: UartPrint("\r\nNo contacts to display please add contacts\r\n"); break;
		case 2:	UartPrint("\r\nContact list full\r\n"); break;
		case 3: UartPrint("\r\nContact name or number already exists\r\n"); break;
		case 4: UartPrint("\r\nEntered name or number doesn't exist in contact list\r\n"); break;
		case 5: UartPrint("\r\nNo calls to display\r\n"); break;
		case 6: UartPrint("\r\nEntered command is wrong\r\n"); break;
		case 7: UartPrint("\r\nEnter correct number\r\n"); break;
		case 8: UartPrint("\r\nUsing LRU structure\r\n"); break;
		case 9: UartPrint("\r\nEnter correct name\r\n"); break;
	}
	return;
}
void printingSuccess(int tempRet)
{
	switch(tempRet)
	{
		case 1: UartPrint("\r\nContact List displayed\r\n"); break;
		case 2: UartPrint("\r\nsuccessfully created\r\n"); break;
		case 3: UartPrint("\r\nSuccessfully deleted\r\n"); break;
		case 4: UartPrint("\r\nSuccessfully edited\r\n"); break;
		case 5: UartPrint("\r\nCallLog List displayed\r\n"); break;
		case 6: UartPrint("\r\nUpdated to callLog list\r\n"); break;
	}
	return;
}

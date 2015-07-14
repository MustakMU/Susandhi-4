#ifndef __STRUCTUREDEFINE_H
#define __STRUCTUREDEFINE_H
#include <stdlib.h>
#include "generic.h"
#include "cpuLoad.h"
typedef struct contactDescriptor
{
	link mylink;
	char number[11];
	char name[10];
}contactDescriptor,*contactPtr_t;
contactDescriptor tempAssignValueContact;

typedef struct callLog
{
	link myCallLog;
	char number[11];
	char name[10];
	char type[4];
	char time[10];
	char duration[3];
}callLog,*callLogPtr_t;
callLog preNodeLog;

typedef struct
{
	LinkPtr (*fun)(LinkPtr,LinkPtr);
}function;

typedef enum checkValue { yes,no
}checkValue;

#include "compareFunction.h"
#include "gpioUartInit.h"
#include "display.h"
LinkPtr getNameOrNum(contactPtr_t assignContact,LinkPtr head,callLogPtr_t nodeLog);
LinkPtr create(LinkPtr head,LinkPtr headLog);
LinkPtr DeleteContact(LinkPtr head,LinkPtr headLog);
LinkPtr editContact(LinkPtr head,LinkPtr headLog);
LinkPtr makecall(LinkPtr head,LinkPtr headLog);
LinkPtr endcall(LinkPtr head,LinkPtr headLog);

void sleep(void);
void  UartInit(uint32_t baudRate);
void UartPrint(char* outStr);
typedef struct queue
{
	int start;
	int end;
	void* queueArray[10];
}nameQueue_t;

nameQueue_t myQueue;
int isQueueFull(nameQueue_t *myQueue);
int isQueueEmpty(nameQueue_t *myQueue);
nameQueue_t* enqQueue(nameQueue_t *myQueue,void * element);
void * deqQueue(nameQueue_t *myQueue);
void queueInit();
char* intToChar(int num,char *chars);
#endif

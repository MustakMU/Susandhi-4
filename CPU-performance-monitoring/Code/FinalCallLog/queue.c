#include "structureDefine.h"
void queueInit()
{
	int i=0;
	myQueue.start=0;
	myQueue.end=0;
	for(i=0;i<10;i++)
	{
		myQueue.queueArray[i]=NULL;
	}
}
int isQueueFull(nameQueue_t *myQueue)
{
	return (myQueue->end+1)%10==myQueue->start;
}
int isQueueEmpty(nameQueue_t *myQueue)
{
	return (myQueue->start)==myQueue->end;
}
nameQueue_t* enqQueue(nameQueue_t *myQueue,void * element)
{
	myQueue->queueArray[myQueue->end]=element;
	myQueue->end++;
	myQueue->end=(myQueue->end)%10;
	return myQueue;
}
void * deqQueue(nameQueue_t *myQueue)
{
	void * queueChar=myQueue->queueArray[myQueue->start];
	myQueue->start++;
	myQueue->start=(myQueue->start)%10;
	return queueChar;
}

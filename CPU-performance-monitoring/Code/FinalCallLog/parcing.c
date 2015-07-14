#include "gpioUartInit.h"
#include "structureDefine.h"
extern char *array[8];
extern int secCount;
extern char previousCommand[4];
function ptrFxn[]={{commands},{displayContactList},{create},{DeleteContact},{editContact},
					{displayCallLog},{cpuLoad},{getCpuLoad},{makecall},{endcall}
				};

int parsing(char *string,LinkPtr headContact,LinkPtr headCallLog)
{

	int i=0,j=0,k=0;
	k=11;
	j=k;
	k=j;
   	char *choice;
   	choice=strtok(string," ");
   	if(strcmp(choice,"cpu")==0)
   	{
   		getCpuLoad(headContact,headCallLog);
   		return 0;
   	}
   	UartPrint("\r\n");
   	for(i=0;i<9;i++)
   	{
   		if(strcmp(array[i],choice)==0)
   		{
   	   		funRetValue=ptrFxn[i].fun(headContact,headCallLog);
   	   		strcpy(previousCommand,choice);
   	   		return 0;
   		}
   	}
   	printingError(6);
	return 0;
}

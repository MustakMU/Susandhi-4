#include "structureDefine.h"
extern int checkContactOrLog;
extern char *previousCommand;

LinkPtr getNameOrNum(contactPtr_t assignContact,LinkPtr head,callLogPtr_t nodeLog)
{
	previousCommand=strtok(NULL," ");
	if(previousCommand==NULL)
	{
		printingError(6);
		return head;
	}
	if(strcmp(previousCommand,"-na")==0)
	{
		previousCommand=strtok(NULL," ");
		if(previousCommand==NULL)
		{
			printingError(6);
			return head;
		}
		if(checkName(previousCommand)==no)
		{
			printingError(9);
			return head;
		}
		if(assignContact==NULL)
		{
			strcpy((nodeLog)->name,previousCommand);
			checkContactOrLog=1;
			funRetValue=linearsearch((LinkPtr)head,(LinkPtr)(nodeLog),cmpNameFxn);
			if(funRetValue!=NULL)
			{
				return funRetValue;
			}
			else
			{
				printingError(4);
			}
		}
		else
		{
			strcpy(assignContact->name,previousCommand);
			checkContactOrLog=1;
			return linearsearch((LinkPtr)head,(LinkPtr)assignContact,cmpNameFxn);
		}
	}
	else if(strcmp(previousCommand,"-nu")==0)
	{
		previousCommand=strtok(NULL," ");
		if(previousCommand==NULL)
		{
			printingError(6);
			return head;
		}
		if(checkNumber(previousCommand)==no)
		{
			printingError(7);
			return head;
		}
		if(assignContact==NULL)
		{
			strcpy((nodeLog)->number,previousCommand);
			checkContactOrLog=1;
			return linearsearch((LinkPtr)head,(LinkPtr)(nodeLog),cmpNumberFxn);
		}
		else
		{
			strcpy(assignContact->number,previousCommand);
			checkContactOrLog=1;
			return linearsearch((LinkPtr)head,(LinkPtr)assignContact,cmpNumberFxn);
		}
	}
	else
	{
		printingError(6);
	}
	return head;
}

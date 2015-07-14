#ifndef __GENERIC_H
#define __GENERIC_H


#include<stdlib.h>
#include<string.h>
typedef struct link
{
	struct link *nextContact;
	struct link *previousContact;
}link,*LinkPtr;
LinkPtr funRetValue,headContact,headCallLog;

typedef int  (*cmpfxn_t) (LinkPtr node, LinkPtr data);

LinkPtr createList(LinkPtr head);
LinkPtr insert(LinkPtr head, LinkPtr node);
LinkPtr sort(LinkPtr head,LinkPtr node,cmpfxn_t cmpNameFxn);
LinkPtr deletion(LinkPtr node);
LinkPtr linearsearch(LinkPtr head,LinkPtr data, cmpfxn_t myfnx);

#endif

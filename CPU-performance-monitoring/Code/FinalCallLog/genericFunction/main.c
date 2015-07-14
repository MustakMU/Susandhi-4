#include "generic.h"

LinkPtr createList(LinkPtr head)
{
	head->nextContact=head;
	head->previousContact=head;
	return head;
}
LinkPtr insert(LinkPtr head, LinkPtr node)
{
    node->nextContact=head->nextContact;
    node->nextContact->previousContact=node;
	head->nextContact=node;
	node->previousContact=head;
	return head;
}
LinkPtr sort(LinkPtr head,LinkPtr node,cmpfxn_t cmpNameFxn)
{
	LinkPtr temp;
	temp=head->nextContact;
	if(temp==head)
	{
		insert(head,node);
		return head;
	}
	else
	{
		while(1)
		{
			if(cmpNameFxn(temp,node)>0)
			{
				temp=insert(temp->previousContact,node);
				break;
			}
			else
			{
				if(temp->nextContact!=head)
				{
					temp=temp->nextContact;
				}
				else
				{
					temp=insert(temp,node);
					break;
				}
			}
		}
		return head;
	}
}
LinkPtr deletion(LinkPtr node)
{
	node->previousContact->nextContact=node->nextContact;
	node->nextContact->previousContact=node->previousContact;
	return node;
}
LinkPtr linearsearch(LinkPtr head,LinkPtr data, cmpfxn_t myfnx)
{
	LinkPtr temp;
	int value;
	temp=head->nextContact;
	while(temp!=head)
	{
		value=myfnx(temp,data);
		if(value==0)
		{
			return temp;
		}
		temp=temp->nextContact;
	}
	return NULL;
}

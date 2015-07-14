#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "structureDefine.h"

LinkPtr commands(LinkPtr head,LinkPtr headLog);
LinkPtr displayContactList(LinkPtr head,LinkPtr headLog);
LinkPtr displayCallLog(LinkPtr head,LinkPtr headLog);
void printingError(int tempRet);
void printingSuccess(int tempRet);


#endif

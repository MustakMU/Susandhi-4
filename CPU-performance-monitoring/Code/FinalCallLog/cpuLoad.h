
#ifndef __CPULOAD_H
#define __CPULOAD_H

#include "structureDefine.h"
void dataPush();
void SysTick_Handler(void);
LinkPtr getCpuLoad(LinkPtr head,LinkPtr headLog);
LinkPtr cpuLoad(LinkPtr head,LinkPtr headLog);
#endif

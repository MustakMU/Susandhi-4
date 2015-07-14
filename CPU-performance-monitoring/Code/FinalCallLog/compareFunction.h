#ifndef __COMPAREFUNCTION_H
#define __COMPAREFUNCTION_H

int cmpNameFxn(LinkPtr node, LinkPtr data);
int cmpNumberFxn(LinkPtr node, LinkPtr data);
checkValue checkNumber(char number[]);
checkValue checkName(char name[]);
void numToChar(int value,callLogPtr_t nodeLog);
int getTimeOfCall(int time,int j,callLogPtr_t nodeLog);
#endif

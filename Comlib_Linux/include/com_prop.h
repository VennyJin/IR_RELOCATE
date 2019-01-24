#ifndef COM_PROP_H
#define COM_PROP_H

#include "comlib.h"

void TestSend(float x,float y,float z);

unsigned char  TestSend(COM_Frame ReadFrame);
#endif

void COMReceive(DoubleComDataType* data);

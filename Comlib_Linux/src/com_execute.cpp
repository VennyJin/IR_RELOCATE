#include "../include/com_prop.h"

void RT_Serial::ProcessData(COM_Frame *RecFrame)
{
   feedDog=0;
   switch(RecFrame->Prop)
   {
    case 0:
       COMReceive(&(RecFrame->Data));
       printf("处理值\n");
       break;
     defalut:
       break;
   }
}

void COMReceive(DoubleComDataType* data)
{
    printf("%d",1);
    printf("%d",data->uint8_ts[0]);
    //data->
}

#include "../include/com_prop.h"

extern RT_Serial IMUCom;

void TestSend(float x, float y,float z)
{
   COM_Frame SendFrame;
   SendFrame.Length=12;
   SendFrame.Prop=50;
   SendFrame.Data.floats_ts[0]=x;
   SendFrame.Data.floats_ts[1]=y;
   SendFrame.Data.floats_ts[2]=z;
//   SendFrame.Data.floats_ts[3]=s;
   IMUCom.FRAME_Send(&SendFrame);
}

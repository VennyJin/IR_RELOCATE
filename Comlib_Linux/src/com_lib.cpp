#include"../include/comlib.h"

#define COM_FRAME_MAX_LENGTH 0XE0

#define HEAD_DETECT       0
#define LENGTH_ACQUIRE    1
#define PROP_ACQUIRE      2
#define DATA_ACQUIRE      3
#define TAIL_CONFIRM      4

void RT_Serial::ByteRead(unsigned char data)
{
  FRAME_Read(data,&FrameRecStatus,&Frame);
}


void RT_Serial::FRAME_Read(unsigned char data,FrameRecStatusTypedef * pRecInfo,COM_Frame *pFrame)
{
    unsigned char RecStatus=pRecInfo->RecStatus;
    unsigned char preData=pRecInfo->preData;
    if(COM_FRAME_MARK==data && TAIL_CONFIRM!=RecStatus )
  {
     if(COM_FRAME_ESCAPE!=preData)
     {
       pRecInfo->RecStatus== HEAD_DETECT;
       RecStatus = HEAD_DETECT;
     }
     else
        {
            if(pFrame->Length > 0)
            {
                pFrame->Length--;
            }
        }
  }
    switch(RecStatus)
    {
        case HEAD_DETECT:
                pRecInfo->RecStatus = LENGTH_ACQUIRE;
            break;

        case LENGTH_ACQUIRE:
                if(data < 4)
                {
                   pRecInfo->RecStatus = HEAD_DETECT;
                }
                else
                {
                    pRecInfo->RecLength = data;
                    pFrame->Length = 0;
                    pRecInfo->RecStatus = PROP_ACQUIRE;
                }
            break;

        case PROP_ACQUIRE:
                pFrame->Prop = data;
                if(pRecInfo->RecLength == 4)//command,only don't contain data
                {
                    pRecInfo->RecStatus = TAIL_CONFIRM;
                }
                else
                {
                    pRecInfo->RecStatus = DATA_ACQUIRE;
                }
            break;

        case DATA_ACQUIRE:
                pRecInfo->RecLength--;
                pFrame->Data.uint8_ts[pFrame->Length++] = data;
                if(pRecInfo->RecLength == 4)
                {
                    pRecInfo->RecStatus = TAIL_CONFIRM;
                }
            break;
        case TAIL_CONFIRM:
                    if(COM_FRAME_MARK == data)
                    {
                        ProcessData(pFrame);
                    }
                    pRecInfo->RecStatus = HEAD_DETECT;
            break;
        default:break;
    }
    pRecInfo->preData = data;
}


void RT_Serial::FRAME_Send(COM_Frame* SendFrame)
{
    unsigned short i = 0;
    unsigned char * SendBufTemp;
    unsigned char SendBuf[COM_FRAME_MAX_LENGTH];
    unsigned char length = SendFrame->Length;
    unsigned char lengthTemp = length;
    SendBufTemp = &SendBuf[0];

    *SendBufTemp++ = (char)COM_FRAME_MARK;
    *SendBufTemp++ = length;
    *SendBufTemp++ = SendFrame->Prop;

    for(i = 0;i < length ;i++)
    {
        char temp = SendFrame->Data.int8_ts[i];

        if((uint8_t)(temp) == COM_FRAME_MARK)
        {
         *SendBufTemp++ = (char)COM_FRAME_ESCAPE;
         lengthTemp ++;

        }
        *SendBufTemp++ = temp;
    }
    *SendBufTemp++ = (char)COM_FRAME_MARK;
    lengthTemp += 4;
    SendBuf[1] = lengthTemp;
    SerialWrite(SendBuf,lengthTemp);
}



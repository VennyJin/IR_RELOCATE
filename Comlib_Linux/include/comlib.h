#ifndef COMLIB_H
#define COMLIB_H
#include"../include/SerialCom.h"
#define COM_FRAME_MARK 0XEE
#define COM_FRAME_ESCAPE 0xFF

union DoubleComDataType
{
  signed char int8_ts[64];
  short int16_ts[32];
  int int32_tw[16];
  unsigned char uint8_ts[64];
  unsigned short uint16_ts[32];
  unsigned int uint32_ts[16];
  float floats_ts[16];
};

struct COM_Frame
{
  unsigned char Length;
  unsigned char Prop;
  DoubleComDataType Data;

};

struct FrameRecStatusTypedef
{
    unsigned char RecStatus =0;
    unsigned char RecCounts=0;
    unsigned char preData=0;
    unsigned char RecLength=0;
};

enum DEVICE_ERR_TYPE
{
    NO_ERR,
    SERIAL_UNCONNECT,
    DEVICE_UNCORRESPOND,
};

class RT_Serial:public VC_Serial
{
public:
    void FRAME_Send(COM_Frame *SendFrame);
private:
    void ByteRead(unsigned char data);
    void FRAME_Read(unsigned char data,FrameRecStatusTypedef *pRecInfo ,COM_Frame *pFrame);
    void ProcessData(COM_Frame *RecFrame);
    FrameRecStatusTypedef FrameRecStatus;
    COM_Frame Frame;
    unsigned char feedDog=0;
};

#endif

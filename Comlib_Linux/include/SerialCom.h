#pragma once
#include <stdio.h>   /* Standard input/output definitions */
#include <string>    /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <cstring>
#include <pthread.h>
#include <aio.h>

#define INVALID_THREAD_VALUE -1   //创建线程失败返回值

const int  REC_BUFF_SIZE=1024;

class VC_Serial
{
public:
   int OpenSerialPort(unsigned char SerialNum,int BaudRate);   
   int CloseSerialPort(); 
   int SerialWrite(unsigned char *TBuff,unsigned char Tlen);
   VC_Serial();   //unfinish
   ~VC_Serial();   //unfinish
private:
   int fd=-1; //文件的fields
   void SerialRead();   //读线程函数
   //  virtual void ByteRead(unsigned char data);
   virtual void ByteRead(unsigned char data)=0;
  
   int hThreadRead=INVALID_THREAD_VALUE;  //读线程句柄
   int CreateReadThread(void );
   
   pthread_t read_thread;   
   
   bool IsFirstWrite;
   unsigned char preTLen;
   static void * ReadThread(void *pParam)
   {
      VC_Serial *pSerial=(VC_Serial *)pParam;
      pSerial->SerialRead(); 
  } 
};


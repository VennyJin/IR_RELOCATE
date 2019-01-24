#include"../include/comlib.h"
#include"../include/com_prop.h"
#include"../include/SerialCom.h"
#include<iostream>
#include"include/main.h"
#include<aio.h>

using namespace std;
extern int Get_State;
VC_Serial::VC_Serial()
{
    //memset()
    IsFirstWrite=true;
}

VC_Serial::~VC_Serial()
{
  //  pthread_exit(NULL);
}

int VC_Serial::SerialWrite(unsigned char *TBuff,unsigned char TLen)
{

  unsigned long wCount=0;
  struct aiocb wr;
//  struct aiocb wr1;

  int ret;
  bzero(&wr,sizeof(wr));

  wr.aio_buf=TBuff;
  wr.aio_fildes=fd;
  wr.aio_nbytes=TLen;
  wr.aio_offset=1000;
//  bzero(&wr1,sizeof(wr1));

//  wr1.aio_buf=TBuff;
//  wr1.aio_fildes=fd;
//  wr1.aio_nbytes=TLen;

    
  struct aiocb *aiocb_list[1];

//  aiocb_list[1]=NULL;
  aiocb_list[0]=&wr;

  if(!IsFirstWrite)
  {

     ret=aio_write(&wr);

     if(ret<0)
      {
         printf("send_data 失败\n");
         return false;
      }

     // while(aio_error(&wr)==EINPROGRESS);   
     int a = aio_suspend(aiocb_list,1,NULL);

     ret=aio_return(&wr);
       
        if(ret!=preTLen)
        { 
           printf("写了%d字节,但是和之前字节数不相等\n",ret);
           return false;
        }
       printf("写了%d字节，和之前一样\n",ret);
      
      return true;  
  }
  
  ret=aio_write(&wr);
  if(ret<0)
    return false;
 // while(aio_error(&wr)==EINPROGRESS);
  aio_suspend(aiocb_list,1,NULL);
  IsFirstWrite=false; 
  preTLen=TLen;
  
  ret=aio_return(&wr);
  printf("写了%d字节\n",ret);
 // free(wr.aio_buf);
  return true;

}

int VC_Serial::OpenSerialPort(unsigned char SerialNum,int BaudRate)
{  
    //string port_name("/dev/ttyUSB");
    //port_name.push_back(SerialNum);     
    // const char * port_name_c=port_name.c_str();
    // const char *port_name_c="/dev/serial/by-id/usb-FTDI_FT232R_USB_UART_AI03TX5L-if00-port0";

    const char *port_name_c="/dev/ttyUSB0";
    // const char *port_name_c="/dev/serial/by-id/usb-Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001-if00-port0";
    //O_NODELAY 非堵塞
    //O_NOCTTY 如果打开的文件时终端设备，不将此设备设置为控制终端
    //O_RDWD 可读可写
    fd=open(port_name_c,O_NOCTTY|O_RDWR);

    if(fd==-1)
    {
      printf("couldn't open the port\n");     
      return -1;
    }
     else 
       fcntl(fd, F_SETFL, 0);  //设置文件锁   之后还得设置

    //配置serialport
    struct termios options;
    //先检查是不是 file descriptor是不时  指向tty device  
    if(!isatty(fd))
    {
       printf("打开的设备不属于串行设备");
       return -1;
    }
   
    memset(&options,0,sizeof(options));  //清空optioins
  
    if( tcgetattr(fd,&options)!=0) //用来获取终端参数 成功返回0  失败返回非0
     {
      printf("get failed\n");
      return -1;
     }
    //设置波特率  最低波特率为9600,最大为115200
    switch(BaudRate)
    { 
      case 115200:
         printf("115200\n");
         cfsetispeed(&options,B115200);
         cfsetospeed(&options,B115200); 
         break;
        // case 76800:
        ///  cfsetispeed(&options,B76800);
        // cfsetospeed(&options,B76800);
        //  break;
       case 57600:
         cfsetispeed(&options,B57600);
         cfsetospeed(&options,B57600);
         break;
       case 38400:
         cfsetispeed(&options,B38400);
         cfsetospeed(&options,B38400);
         break;
      case 19200:
         cfsetispeed(&options,B19200);
         cfsetospeed(&options,B19200);
         break;
      case 9600:
         cfsetispeed(&options,B9600);
         cfsetospeed(&options,B9600);
         break;
       defalt:
         printf("set baudrate faile\n");
         return -1;
    }
   
    //Enable the receiver and set local mode
      options.c_cflag|=(CLOCAL|CREAD);
  
    //setting character size
      options.c_cflag&=~CSIZE;
      options.c_cflag|=CS8;  //8位数据位
    //setting parity  
      options.c_cflag&=~PARENB; //无校验位
    //setting stopbits
      options.c_cflag&=~CSTOPB;  //一位停止位

    //设置读超时 
    //read 调用读到数据立即返回，否则将为每个字符最多等待VTIME×100ms时间
    //在阻塞模式下运行 
      options.c_cc[VTIME]=1;
      options.c_cc[VMIN]=0;

    //set the new options for  the port
    //TCSANOW  represents  make changes now without waiting for data to complete
    if( tcsetattr(fd,TCSANOW,&options)!=0)
   {
       printf("set failed");
       return -1;
   }   
    
   //刷新输入和输出队列,清楚缓存区
    if(tcflush(fd,TCIOFLUSH)!=0)
  {
      printf("清除缓存区失败\n");
      return -1;
  }

    if(CreateReadThread()==-1)
  {
      printf("线程开启失败\n");
      return -1;
  } 

    printf("开启成功\n");
    return 0;    

}

int VC_Serial::CloseSerialPort()
{
  if(close(fd)==-1)
  {
    printf("close fd:%d failed\n ",fd);
    return -1; 
  }
  else
   {
     /* if(pthread_cancel(read_thread)!=0)
      {
       printf("线程取消失败\n");
       return -1;
      }
     printf("读线程关闭成功\n"); 
     hThreadRead=INVALID_THREAD_VALUE;*/
     printf("关闭成功\n");  
   }

  pthread_exit(NULL);   
  return 0;

}

void VC_Serial::SerialRead()
{
    int ret;
    printf("进入读线程\n");
    char buf[REC_BUFF_SIZE+1];

    struct aiocb my_aiocb;
    bzero((char *)&my_aiocb,sizeof(my_aiocb));
    //看一下 aiocb_suspend

    struct aiocb *aiocb_list[1];
  
    my_aiocb.aio_buf=buf;
    my_aiocb.aio_fildes=fd;
    my_aiocb.aio_nbytes=REC_BUFF_SIZE;
    my_aiocb.aio_offset=-500;
   
    aiocb_list[0]=&my_aiocb;
    while(1)
    {
        ret=aio_read(&my_aiocb);
        if(ret<0)
        {
            printf("aio_read_error\n");
            return ;
        }
        //printf("调用完毕读函数\n");
        //轮巡检差  后面可以用操作系统来通知  或者让操作系统完成读后主动创建一个
        //while(aio_error(&my_aiocb)==EINPROGRESS);
        aio_suspend(aiocb_list,1,NULL);
        int read_number=aio_return(&my_aiocb);
        if(read_number==1)
        {
            printf("\nreturn number :%d  ",read_number);

            for(int i=0;i<read_number;i++)
            {
                printf("%x ",buf[i]);
                Get_State=buf[i];
                ByteRead(buf[i]);
            }
        }
        }
}

int VC_Serial::CreateReadThread()
{

  if(hThreadRead==INVALID_THREAD_VALUE)
  {
    hThreadRead=pthread_create(&read_thread,NULL,ReadThread,this);
  }
  if(hThreadRead==INVALID_THREAD_VALUE)
  {
    printf("创建读线程失败\n");
    return -1;
  }
  else
  printf("创建读线程成功\n");

  return 0;
}


#include"../include/com_prop.h"
#include"../include/SerialCom.h"
#include<iostream>
using namespace std;
RT_Serial IMUCom;
int Get_State=0;
int main()
{ 
   unsigned char num='1';
   double x = 5.00;
   double y = 4.90;

   IMUCom.OpenSerialPort(num,115200);
   while (1)
   {
       if(Get_State)
           cout<<Get_State;
   //CreateReadThread();
   TestSend(x,y);
   getchar();
   }
}

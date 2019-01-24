#include "../GETTIME/gettime.h"


static bool is_first_use=true;
static double time_start=0;

//gettime  ms
double  gettime()
{
    struct timeval tv;
    double  time;
    gettimeofday(&tv,NULL);
    if(is_first_use)
    {
        is_first_use=false;
        time_start=tv.tv_usec/1000.0+tv.tv_sec*1000;
        
        time=0;
    }
    else
    {
        time=tv.tv_usec/1000.0+tv.tv_sec*1000.0-time_start;
        
    }
    return time;
    
}
double  getabsolutetime()
{
    struct timeval tv;
    double  time;
    gettimeofday(&tv,NULL);
    time=tv.tv_usec/1000.0+tv.tv_sec*1000.0;
    return time;
}
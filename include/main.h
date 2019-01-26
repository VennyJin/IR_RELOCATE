#ifndef _MAIN_H
#define _MAIN_H

//opencv
#include <opencv2/opencv.hpp>
#include "cv.h"
#include "highgui.h"
#include <vector>

//c
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

//C++
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stack>

//my head.h
#include "ImageProcess.h"
#include "GetLocation.h"
#include "Comlib_Linux/include/comlib.h"
#include "Comlib_Linux/include/com_prop.h"
#include "Comlib_Linux/include/SerialCom.h"
#include "GETTIME/gettime.h"

using namespace std;
using namespace cv;

extern float z1,z3;
extern double time1;
extern double last_time1;
extern string ImgName;
extern Mat camera_matrix;
extern Mat distortion_coefficients;
//data
#define   IMAGE_1280 1
//#define   IMAGE_640 1

#ifdef IMAGE_1280
#define   IMAGE_X  1280
#define   IMAGE_Y  720
#endif

#ifdef IMAGE_640
#define   IMAGE_X  640
#define   IMAGE_Y  480
#endif

#define IMG_SUM 19
#define POINTS_NUM 6

#define USE_CAMERA 1
//#define USE_AVI 1
//#define USE_IMAGE 1               //multiple pic
//#define TEST_IMAGE 1              //single pic

#define TEXTSEND 1              //是否串口发送数据
//#define IMSHOW 1                //是否显示图像
#define TEST 1                  //是否显示数据
#define SAVE_AVI 1


#define pi    3.14159265358979f


#endif

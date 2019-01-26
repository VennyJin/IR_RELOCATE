#include "include/main.h"

//Mat src_img = Mat::zeros(IMAGE_Y, IMAGE_X, CV_16UC3);
Mat src_img;
double time1;
double last_time1;
string ImgName;
extern int get_flag;
extern float centertheta;
extern float z1,z3;
RT_Serial IMUCom;

extern float z1,z3;
extern  float centertheta;

#ifdef IMAGE_640 
    //6mm640	
    double camD[9] = { 9.4836092962461146e+02, 0., 3.1775949114303734e+02, 0.,
   9.4873849250642172e+02, 2.3265580851461698e+02, 0., 0., 1.  };
    //distortion coefficient
    double distCoeffD[5] = { -3.5669196592485664e-01, -6.8220109038984389e-01,
   -2.3024860074375773e-03, 3.9458245353479957e-03,
   3.7266594804827875e+00 };
#endif

#ifdef IMAGE_1280
    //6mm1280
    //intrinsic parameter
    double camD[9] = { 2.0988910422516487e+03, 0., 6.4910784101225329e+02, 0.,
   2.0997650367742913e+03, 3.2739615903249341e+02, 0., 0., 1.  };
    //distortion coefficient
    double distCoeffD[5] = { -3.7251556939756514e-01, -4.5327507470353723e-01,
   -2.8442860362404452e-03, 4.2802675292896442e-03,
   3.5241787390258472e+00 };//0.8
    /*double camD[9] = { 2.0847275298500317e+03, 0., 6.2266849096448402e+02, 0.,
       2.0869223924978387e+03, 3.3146447234228793e+02, 0., 0., 1.  };
    //distortion coefficient
    double distCoeffD[5] = { -3.2960044224737362e-01, -6.8084918063540545e-01,
       1.2652966475725862e-03, 5.2738493394313092e-03,
       3.8011541506675810e+00 };//0.6*/
#endif

    cv::Mat camera_matrix = cv::Mat(3, 3, CV_64FC1, camD);
    cv::Mat distortion_coefficients = cv::Mat(5, 1, CV_64FC1, distCoeffD);

int main()
{
    Mat map1, map2;
    Size imageSize;
    imageSize.width= IMAGE_X;
    imageSize.height= IMAGE_Y;
    //Distortion Rectify
    initUndistortRectifyMap(camera_matrix, distortion_coefficients, Mat(),
    getOptimalNewCameraMatrix(camera_matrix, distortion_coefficients, imageSize, 1, imageSize, 0),
    imageSize, CV_16SC2, map1, map2);
    int g_get_key = 0;

#ifdef TEXTSEND
    // open serial port
    IMUCom.OpenSerialPort(0,115200);
#endif

#ifdef USE_IMAGE
    ifstream fin("6mm1280thnames.txt");//打开原始样本图片文件列表
#endif

#ifdef USE_CAMERA   
    VideoCapture capture(1);
    Mat frame;
	capture.set(CV_CAP_PROP_FRAME_WIDTH, IMAGE_X);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGE_Y);
	if (!capture.isOpened())
	{
        printf("can not open camera\n");
		return -1;
	}
    #ifdef SAVE_AVI
        VideoWriter vid;
        vid.open("cam.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25, Size(IMAGE_X, IMAGE_Y), true);
    #endif
#endif

#ifdef USE_AVI
	VideoCapture capture;
    Mat frame;
    capture.open("20190117205513308.avi");
    if (!capture.isOpened())
	{
		printf("can not open ...\n");
		return -1;
	}
#endif

	while (g_get_key != 27)
	{
//////////////////////////////////////////////////////////////////////////////
#ifdef USE_CAMERA
		TickMeter tm2;
        tm2.start();
		capture>>src_img;
    #ifdef TEST
            tm2.stop();
            cout<<"capture time:"<<tm2.getTimeMilli()<<endl;
            last_time1=time1;
            time1=gettime();
            cout<<"TOTAL_TIME= "<<time1-last_time1<<endl;
            TickMeter tm1;
            tm1.start();
    #endif

            ImageProcess();
            GetLocation();

    #ifdef TEXTSEND
                    if(get_flag==1)
            {
                TestSend(z3,z1,centertheta);
            }

                 else if(get_flag==0)
            {
                TestSend(0,0,0);
            }
    #endif

    #ifdef TEST
            tm1.stop();
            cout<<" image process and calculation time and textsend time= "<<tm1.getTimeMilli()<<endl;
    #endif

    #ifdef SAVE_AVI
            capture>>frame;
            #ifdef IMSHOW
            imshow("capture image",frame);
            #endif
            vid << frame;
            waitKey(1);
    #endif


#endif
/////////////////////////////////////////////////////////////////////////
#ifdef USE_IMAGE
        int img_num = 1;
        getline(fin,ImgName); //一行一行读取文件列表
        if(ImgName.empty())
             break;
        string ImgName1;
        ImgName1 = "6mm1280th/" + ImgName+"-4389.jpg";
        src_img= imread(ImgName1);//读取图片
        if(src_img.data ==0)
        {return -1;}
#endif
///////////////////////////////////////////////////////////////////////////
#ifdef TEST_IMAGE
        src_img = imread("6mm1280/6351.jpg");
#endif
///////////////////////////////////////////////////////////////////////////
#ifdef USE_AVI
        TickMeter tm2;
        tm2.start();
        capture>>src_img;
        if(src_img.empty())
             break;
        #ifdef TEST
                tm2.stop();
                cout<<"capture time:"<<tm2.getTimeMilli()<<endl;
                last_time1=time1;
                time1=gettime();
                cout<<"TOTAL_TIME= "<<time1-last_time1<<endl;
                TickMeter tm1;
                tm1.start();
        #endif

        ImageProcess();
        GetLocation();

        #ifdef TEXTSEND
                if(get_flag==1)
                {
                    TestSend(z3,z1,centertheta);
                }

                else if(get_flag==0)
                {
                    TestSend(0,0,0);
                }

        #endif

        #ifdef TEST
                tm1.stop();
                cout<<" image process and calculation time and textsend time= "<<tm1.getTimeMilli()<<endl;
        #endif

#endif
        waitKey(1);
	}

#ifdef USE_CAMERA
    capture.release();
    #ifdef SAVE_AVI
        vid.release();
    #endif
#endif

#ifdef USE_AVI
    capture.release();
#endif
	return 0;
}

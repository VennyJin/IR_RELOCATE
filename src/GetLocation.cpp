#include "include/main.h"

vector<cv::Point2f> Points2D;
vector<cv::Point2f> Points2D_1;
float goal_x[3];
float goal_z[3];
float goal_z3[3];
float goal_theta[3];
float z1,z3;
float centertheta;
extern int get_flag;
extern Point2f goal_point[POINTS_NUM];

int Get_State=0;

int64_t getCurrentTime()
    {
       struct timeval tv;
       gettimeofday(&tv,NULL);
       return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }

float bubble_sort3(float *arr)
{
	if(arr[0] > arr[1])
        swap(arr[0], arr[1]);
    if(arr[1] > arr[2])
        swap(arr[1], arr[2]);
    if(arr[0] > arr[1])
        swap(arr[0], arr[1]);
}
void bubble_sort(float *arr, int len)
{
        if (len > 1)
        {
                int i, j;
        for (i = 0; i < len - 1; i++)
            for (j = 0; j < len - 1 - i; j++)
                                if (arr[j] > arr[j + 1])
                                        swap(arr[j], arr[j + 1]);
        }
}
int GetLocation(void)
{
    #ifdef TEST
    ofstream outputfile;
    outputfile.open("data.txt", ios::binary | ios::app | ios::in | ios::out);
    #endif

    #ifdef USE_IMAGE
    ofstream outputfileline;
    outputfileline.open("dataline.txt", ios::binary | ios::app | ios::in | ios::out);
    ofstream outputfilelinez3;
    outputfilelinez3.open("datalinez3.txt", ios::binary | ios::app | ios::in | ios::out);
    ofstream outputfileline00;
    outputfileline00.open("dataline00.txt", ios::binary | ios::app | ios::in | ios::out);
    #endif

	vector<cv::Point3f> RealPoints3D;
	vector<cv::Point3f> RealPoints3D_1;
    vector<cv::Point3f> RealPoints3Dx;
	vector<cv::Point3f> RealPoints3D_1x;
    vector<cv::Point3f> RealPoints3Dxx;
	vector<cv::Point3f> RealPoints3D_1xx;
//	if (POINTS_NUM == 4)
//	{
//        RealPoints3D.push_back(cv::Point3f(0, 150, 0));        //P1 ×óÉÏ
//		RealPoints3D.push_back(cv::Point3f(0, 0, 0));      //P2 ×óÏÂ ×ø±êÔ­µã
//        RealPoints3D.push_back(cv::Point3f(150, 150, 0));      //P3	ÓÒÉÏ
//        RealPoints3D.push_back(cv::Point3f(150, 0, 0));    //P4 ÓÒÏÂ
//	}
	if (POINTS_NUM == 6)
	{
		//x.y.z
		/*RealPoints3D.push_back(cv::Point3f(0, 110, 0));        //P1 ×óÉÏ
		RealPoints3D.push_back(cv::Point3f(0, 0, 0));      //P2 ×óÏÂ ×ø±êÔ­µã
		RealPoints3D.push_back(cv::Point3f(120, 110, 0));      //P3	ÖÐÉÏ
		RealPoints3D.push_back(cv::Point3f(120, 0, 0));    //P4 ÖÐÏÂ
		RealPoints3D_1.push_back(cv::Point3f(120, 110, 0));      //P3	ÖÐÉÏ
		RealPoints3D_1.push_back(cv::Point3f(120, 0, 0));    //P4 ÖÐÏÂ
        RealPoints3D_1.push_back(cv::Point3f(197.793, 110, 77.793));      //P5	ÓÒÉÏ
		RealPoints3D_1.push_back(cv::Point3f(197.793, 0,77.793));    //P6 ÓÒÏÂ*/
        //one axis  z
		RealPoints3D.push_back(cv::Point3f(-246, 386, 257));        //P1 ×óÉÏ
		RealPoints3D.push_back(cv::Point3f(-252, 128, 257));      //P2 ×óÏÂ ×ø±êÔ­µã
		RealPoints3D.push_back(cv::Point3f(0, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3D.push_back(cv::Point3f(0, 373, 0));    //P4 ÖÐÏÂ
		RealPoints3D_1.push_back(cv::Point3f(0, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3D_1.push_back(cv::Point3f(0, 373, 0));    //P4 ÖÐÏÂ
        RealPoints3D_1.push_back(cv::Point3f(361, 644, 0));      //P5	ÓÒÉÏ
		RealPoints3D_1.push_back(cv::Point3f(361, 517, 0));
        //one axis  for x
		RealPoints3Dx.push_back(cv::Point3f(-354, 386, 0));        //P1 ×óÉÏ
		RealPoints3Dx.push_back(cv::Point3f(-360, 128, 0));      //P2 ×óÏÂ ×ø±êÔ­µã
		RealPoints3Dx.push_back(cv::Point3f(0, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3Dx.push_back(cv::Point3f(0, 373, 0));    //P4 ÖÐÏÂ
		RealPoints3D_1x.push_back(cv::Point3f(0, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3D_1x.push_back(cv::Point3f(0 , 373, 0));    //P4 ÖÐÏÂ
        RealPoints3D_1x.push_back(cv::Point3f(252.7, 644, 257.71));      //P5	ÓÒÉÏ
		RealPoints3D_1x.push_back(cv::Point3f(252.7, 517, 257.71));
        //one axis  for x
        RealPoints3Dxx.push_back(cv::Point3f(0, 386, -246));        //P1 ×óÉÏ
		RealPoints3Dxx.push_back(cv::Point3f(0, 128, -252));      //P2 ×óÏÂ ×ø±êÔ­µã
		RealPoints3Dxx.push_back(cv::Point3f(257, 579,0 ));      //P3	ÖÐÉÏ
		RealPoints3Dxx.push_back(cv::Point3f(257, 373, 0));    //P4 ÖÐÏÂ
		RealPoints3D_1xx.push_back(cv::Point3f(257, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3D_1xx.push_back(cv::Point3f(257 , 373, 0));    //P4 ÖÐÏÂ
        RealPoints3D_1xx.push_back(cv::Point3f(257, 644, 361));      //P5	ÓÒÉÏ
		RealPoints3D_1xx.push_back(cv::Point3f(257, 517, 361));
		/*//two axises
        RealPoints3D.push_back(cv::Point3f(0, 386, 0));        //P1 ×óÉÏ
		RealPoints3D.push_back(cv::Point3f(0, 128, 0));      //P2 ×óÏÂ ×ø±êÔ­µã
		RealPoints3D.push_back(cv::Point3f(358, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3D.push_back(cv::Point3f(358, 373, 0));    //P4 ÖÐÏÂ
		RealPoints3D_1.push_back(cv::Point3f(0, 579, 0));      //P3	ÖÐÉÏ
		RealPoints3D_1.push_back(cv::Point3f(0, 373, 0));    //P4 ÖÐÏÂ
        RealPoints3D_1.push_back(cv::Point3f(361, 644, 0));      //P5	ÓÒÉÏ
		RealPoints3D_1.push_back(cv::Point3f(361, 517, 0));*/
	}

	//³õÊ¼»¯Ïà»ú²ÎÊýOpencv
    //ultra_v0_0ede
//	double camD[9] = { 9.4980970701340141e+02, 0., 3.3938001715994233e+02, 0.,
//		9.4189316250083039e+02, 2.5516286270284834e+02, 0., 0., 1. };
//	cv::Mat camera_matrix = cv::Mat(3, 3, CV_64FC1, camD);
//	//»û±ä²ÎÊý
//	double distCoeffD[5] = { -4.1675301734897813e-01, 2.0678258765129023e-01,
//		-1.6920292408907273e-03, 3.7305892140614117e-03,
//		2.2199235957231558e-01 };

    //ultra_v1
    //    double camD[9] = { 9.6401049218056232e+02, 0., 3.0757209639934666e+02, 0.,
//                       9.5886897213336761e+02, 2.2877197657543317e+02, 0., 0., 1. };
//    cv::Mat camera_matrix = cv::Mat(3, 3, CV_64FC1, camD);
//    //»û±ä²ÎÊý
//    double distCoeffD[5] = { -4.4319582015279585e-01, 3.3325040642098741e-01,
//                             6.1076833199863474e-03, 2.5617232213955296e-03,
//                             -3.3306926347419927e-02 };
//    //ultra_12mm
    /*double camD[9] = { 4.4786616076149749e+03, 0., 2.8282612976958859e+02, 0.,
                       4.4321497826155010e+03, 3.4738390302238736e+02, 0., 0., 1.  };
    cv::Mat camera_matrix = cv::Mat(3, 3, CV_64FC1, camD);
    //»û±ä²ÎÊý
    double distCoeffD[5] = { -3.8648954639454286e-01, -8.5653354044046477e+00,
                             2.7258856821484457e-03, 8.6715932657081326e-03,
                             4.5940922897229335e+01 };*/
    
	cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat rvec_1 = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat tvec_1 = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat Rvec;
	cv::Mat Rvec_1;
	cv::Mat_<float> Tvec;
	cv::Mat_<float> Tvec_1;
	cv::Mat_<float> rotMat(3, 3);
	cv::Mat_<float> rotMat_1(3, 3);
	Mat P_oc;
	Mat P_oc_1;
    cv::Mat rvecx = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat rvec_1x = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat tvecx = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat tvec_1x = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat Rvecx;
	cv::Mat Rvec_1x;
	cv::Mat_<float> Tvecx;
	cv::Mat_<float> Tvec_1x;
	cv::Mat_<float> rotMatx(3, 3);
	cv::Mat_<float> rotMat_1x(3, 3);
	Mat P_ocx;
	Mat P_oc_1x;
    cv::Mat rvecxx = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat rvec_1xx = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat tvecxx = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat tvec_1xx = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat Rvecxx;
	cv::Mat Rvec_1xx;
	cv::Mat_<float> Tvecxx;
	cv::Mat_<float> Tvec_1xx;
	cv::Mat_<float> rotMatxx(3, 3);
	cv::Mat_<float> rotMat_1xx(3, 3);
	Mat P_ocxx;
	Mat P_oc_1xx;
	if (get_flag == 1)
	{
		
//		if (POINTS_NUM == 4)
//		{
//            Points2D.resize(4);
//            Points2D_1.resize(4);
//			SetPoint2D();
//            solvePnP(RealPoints3D, Points2D, camera_matrix, distortion_coefficients, rvec, tvec, false, CV_ITERATIVE);
//            rvec.convertTo(Rvec, CV_32F);    //Ðý×ªÏòÁ¿
//            tvec.convertTo(Tvec, CV_32F);   //Æ½ÒÆÏòÁ¿
//            cv::Rodrigues(Rvec, rotMat);  //ÓÉÓÚsolvePnP·µ»ØµÄÊÇÐý×ªÏòÁ¿£¬¹ÊÓÃÂÞµÂÀï¸ñË¹±ä»»±ä³ÉÐý×ª¾ØÕó
//            P_oc = -rotMat.inv()*Tvec;
//            for (int k = 0; k < POINTS_NUM; k++)
//            {
//                cout << Points2D[k] << " ";
//            }
//            cout << endl << "x:" << P_oc.ptr<float>(0)[0] << " y:" << P_oc.ptr<float>(0)[1] << " z:" << P_oc.ptr<float>(0)[2] << endl;
//            //±£´æÖÁdata.txt
//            outputfile<<getCurrentTime()<<" "<<P_oc.ptr<float>(0)[2]<<"\n";
//            TestSend(P_oc.ptr<float>(0)[2],0);
//        }
//        //Áù¸öµãµÄÄ£Ê½
        if (POINTS_NUM == 6)
        {
            float theta = pi / 4;//Á½¸öÃæµÄ¼Ð½Ç
			//SetPoint2D();
			/*Points2D[0]=Point2f(307.649, 403.432);
			Points2D[1]=Point2f(307.295, 461.386);
			Points2D[2]=Point2f(363.242, 356.848);
			Points2D[3]=Point2f(363.788, 401.212);
			Points2D_1[0]=Point2f(364.242, 356.848);
			Points2D_1[1]=Point2f(363.788, 401.212);
			Points2D_1[2]=Point2f(437.4, 338.857);
			Points2D_1[3]=Point2f(438.41, 367.713);*/
			/***solvePnP(RealPoints3D, Points2D, camera_matrix, distortion_coefficients, rvec, tvec, false, CV_ITERATIVE);
			rvec.convertTo(Rvec, CV_32F);    //Ðý×ªÏòÁ¿
			tvec.convertTo(Tvec, CV_32F);   //Æ½ÒÆÏòÁ¿
			cv::Rodrigues(Rvec, rotMat);  //ÓÉÓÚsolvePnP·µ»ØµÄÊÇÐý×ªÏòÁ¿£¬¹ÊÓÃÂÞµÂÀï¸ñË¹±ä»»±ä³ÉÐý×ª¾ØÕó
			P_oc = -rotMat.inv()*Tvec;
			cout << " µÚ1¸öÃæ" << endl;
			for (int k = 0; k < 4; k++)
			{
				cout << Points2D[k] << " ";
			}
			cout << endl << "x:" << P_oc.ptr<float>(0)[0] << " y:" << P_oc.ptr<float>(0)[1] << " z:" << P_oc.ptr<float>(0)[2] << endl; 

			solvePnP(RealPoints3D_1, Points2D_1, camera_matrix, distortion_coefficients, rvec_1, tvec_1, false, CV_ITERATIVE);
			rvec_1.convertTo(Rvec_1, CV_32F);    //Ðý×ªÏòÁ¿
			tvec_1.convertTo(Tvec_1, CV_32F);   //Æ½ÒÆÏòÁ¿
			cv::Rodrigues(Rvec_1, rotMat_1);  //ÓÉÓÚsolvePnP·µ»ØµÄÊÇÐý×ªÏòÁ¿£¬¹ÊÓÃÂÞµÂÀï¸ñË¹±ä»»±ä³ÉÐý×ª¾ØÕó
			P_oc_1 = -rotMat_1.inv()*Tvec_1;
			cout << " µÚ2¸öÃæ" << endl;
			for (int k = 0; k < 4; k++)
			{
				cout << Points2D_1[k] << " ";
			}
			cout << endl << "x:" << P_oc_1.ptr<float>(0)[0] << " y:" << P_oc_1.ptr<float>(0)[1] << " z:" << P_oc_1.ptr<float>(0)[2] << endl;
			//¶þÎ¬ÂëÁ½¸öÉî¶È
			float z1 = P_oc.ptr<float>(0)[2];
			float dis_y = P_oc_1.ptr<float>(0)[2];
            if(IMAGE_X == 640)
            {
                z1 =z1*0.92656+544.72;
                dis_y = dis_y*1.0135+198.86;
            }
            if(IMAGE_X == 1280)
            {
                z1 =z1*1.066+68.283;
                dis_y = dis_y*1.0711+61.35;
            }
			float x = sqrt(z1*z1 + dis_y* dis_y - 2 * z1*dis_y*cos(theta));
			float thetax = asin(z1*sin(theta) / x);
			float dis_x = -cos(theta + thetax) / sin(theta)*x;***/
            //¶þÎ¬ÂëÁœžöÉî¶È£š×óÃæÎª»ù×Œ£©
			/*float dis_y = P_oc.ptr<float>(0)[2];//×óÃæ
			float z1 = P_oc_1.ptr<float>(0)[2]; //ÓÒÃæ
			float dis_x = z1*sin(theta) - (dis_y - z1*cos(theta)*tan(theta)); //×óÃæ»ù×Œ*/
			//¶þÎ¬ÂëÁœžöÉî¶È£šÓÒÃæÎª»ù×Œ£©
			/*float z1 = P_oc.ptr<float>(0)[2];//×óÃæ
			float dis_y = P_oc_1.ptr<float>(0)[2]; //ÓÒÃæ
			float dis_x = z1*sin(theta) - (dis_y - z1*cos(theta)*tan(theta)); //ÓÒÃæ»ù×Œ*/
			/***cout << " X = " << dis_x << " Y = " << dis_y << endl << endl;
			cout << " X = " << dis_x << " Y = " << dis_y << endl << endl;
			//outputfile<<"X:"<<dis_x<<"Y:"<<dis_y<<Points2D[0]<<Points2D[1]<<Points2D[2]<<Points2D[3]<<Points2D_1[2]<<Points2D_1[3]<<"\n";
            outputfile<<" z1: "<<z1<<"z2:"<<dis_y<<"x:"<<dis_x<<endl;***/
			//six points for one axis
			vector<cv::Point3f> RealPoints3D6;
			vector<cv::Point2f> Points2D6;
            float temp_x[3];
            float temp_z[3];
            float temp_z3[3];
            float temp_theta[3];
			for(int k=0;k<4;k++)
			{
				RealPoints3D6.push_back(RealPoints3D[k]);
			}
			RealPoints3D6.push_back(RealPoints3D_1[2]);
			RealPoints3D6.push_back(RealPoints3D_1[3]);
			for(int k=0;k<4;k++)
			{
				Points2D6.push_back(Points2D[k]);
			}
			Points2D6.push_back(Points2D_1[2]);
			Points2D6.push_back(Points2D_1[3]);
            centertheta=atan(((Points2D_1[3].x+Points2D[0].x)/2-640)/camera_matrix.at<double>(0,0));
            centertheta=centertheta*180/pi;
			solvePnP(RealPoints3D6, Points2D6, camera_matrix, distortion_coefficients, rvec, tvec, false, CV_EPNP);
            rvec.convertTo(Rvec, CV_32F);       //Ðý×ªÏòÁ¿
            tvec.convertTo(Tvec, CV_32F);       //Æ½ÒÆÏòÁ¿
            cv::Rodrigues(Rvec, rotMat);        //ÓÉÓÚsolvePnP·µ»ØµÄÊÇÐý×ªÏòÁ¿£¬¹ÊÓÃÂÞµÂÀï¸ñË¹±ä»»±ä³ÉÐý×ª¾ØÕó
			P_oc = -rotMat.inv()*Tvec;
            z1=P_oc.ptr<float>(0)[2];
            float sy = sqrt(rotMat.at<float>(0,0) * rotMat.at<float>(0,0) +  rotMat.at<float>(1,0) * rotMat.at<float>(1,0) );
            float thetay;
            #ifdef TEST
            bool singular=sy<1e-6;
            float thetax,thetaz;
            if(!singular){
                thetax=atan2(rotMat.at<float>(2,1), rotMat.at<float>(2,2));
                thetaz=atan2(rotMat.at<float>(1,0), rotMat.at<float>(0,0));
            }else{
                thetax=atan2(-rotMat.at<float>(1,2), rotMat.at<float>(1,1));
                thetaz=0;
            }
            thetax=thetax*180/3.1415926;
            thetaz=thetaz*180/3.1415926;
            #endif
            thetay=atan(-rotMat.at<float>(2,0)/ sy);
            thetay=thetay*180/3.1415926;
            /*float x1=((rotMat.at<float>(1,1)*rotMat.at<float>(2,2)-rotMat.at<float>(1,2)*rotMat.at<float>(2,1))*Tvec[0]+(rotMat.at<float>(0,2)*rotMat.at<float>(2,1)-rotMat.at<float>(0,1)*rotMat.at<float>(2,2))*Tvec[1]+(rotMat.at<float>(0,1)*rotMat.at<float>(1,2)-rotMat.at<float>(0,2)*rotMat.at<float>(1,1))*Tvec[2])/(rotMat.at<float>(0,0)*(rotMat.at<float>(1,1)*rotMat.at<float>(2,2)-rotMat.at<float>(1,2)*rotMat.at<float>(2,1))+rotMat.at<float>(1,0)*(rotMat.at<float>(0,2)*rotMat.at<float>(2,1)-rotMat.at<float>(0,1)*rotMat.at<float>(2,2))+rotMat.at<float>(2,0)*(rotMat.at<float>(0,1)*rotMat.at<float>(1,2)-rotMat.at<float>(0,2)*rotMat.at<float>(1,1)));*/
            vector<cv::Point3f> RealPoints3D6x;
			for(int k=0;k<4;k++)
			{
				RealPoints3D6x.push_back(RealPoints3Dx[k]);
			}
			RealPoints3D6x.push_back(RealPoints3D_1x[2]);
			RealPoints3D6x.push_back(RealPoints3D_1x[3]);
			solvePnP(RealPoints3D6x, Points2D6, camera_matrix, distortion_coefficients, rvecx, tvecx, false, CV_EPNP);
            rvecx.convertTo(Rvecx, CV_32F);     //Ðý×ªÏòÁ¿
            tvecx.convertTo(Tvecx, CV_32F);     //Æ½ÒÆÏòÁ¿
            cv::Rodrigues(Rvecx, rotMatx);      //ÓÉÓÚsolvePnP·µ»ØµÄÊÇÐý×ªÏòÁ¿£¬¹ÊÓÃÂÞµÂÀï¸ñË¹±ä»»±ä³ÉÐý×ª¾ØÕó
			P_ocx = -rotMatx.inv()*Tvecx;
            float z2=P_ocx.ptr<float>(0)[2];
            float syx = sqrt(rotMatx.at<float>(0,0) * rotMatx.at<float>(0,0) +  rotMatx.at<float>(1,0) * rotMatx.at<float>(1,0) );
            float thetayx;
            bool singularx=syx<1e-6;
            #ifdef TEST
            float thetaxx,thetazx;
            if(!singularx){
                thetaxx=atan2(rotMatx.at<float>(2,1), rotMatx.at<float>(2,2));
                thetazx=atan2(rotMatx.at<float>(1,0), rotMatx.at<float>(0,0));
            }else{
                thetaxx=atan2(-rotMatx.at<float>(1,2), rotMatx.at<float>(1,1));
                thetazx=0;
            }
            thetaxx=thetaxx*180/3.1415926;
            thetazx=thetazx*180/3.1415926;
            #endif
            thetayx=atan(-rotMatx.at<float>(2,0)/ syx);
            thetayx=thetayx*180/3.1415926;
            theta=(thetay-thetayx)*pi/180;
            
            //z1=z1*0.95538-46.366;
            //z2=z2*0.95538-46.366;
            //theta=pi/4;
            vector<cv::Point3f> RealPoints3D6xx;
			for(int k=0;k<4;k++)
			{
				RealPoints3D6xx.push_back(RealPoints3Dxx[k]);
			}
			RealPoints3D6xx.push_back(RealPoints3D_1xx[2]);
			RealPoints3D6xx.push_back(RealPoints3D_1xx[3]);
			solvePnP(RealPoints3D6xx, Points2D6, camera_matrix, distortion_coefficients, rvecxx, tvecxx, false, CV_EPNP);
			rvecxx.convertTo(Rvecxx, CV_32F);    //Ðý×ªÏòÁ¿
			tvecxx.convertTo(Tvecxx, CV_32F);   //Æ½ÒÆÏòÁ¿
			cv::Rodrigues(Rvecxx, rotMatxx);  //ÓÉÓÚsolvePnP·µ»ØµÄÊÇÐý×ªÏòÁ¿£¬¹ÊÓÃÂÞµÂÀï¸ñË¹±ä»»±ä³ÉÐý×ª¾ØÕó
			P_ocxx = -rotMatxx.inv()*Tvecxx;
            z3=P_ocxx.ptr<float>(0)[2];
            float syxx = sqrt(rotMatxx.at<float>(0,0) * rotMatxx.at<float>(0,0) +  rotMatxx.at<float>(1,0) * rotMatxx.at<float>(1,0) );
            float thetayxx;
            bool singularxx=syxx<1e-6;
            #ifdef TEST
            float thetaxxx,thetazxx;
            if(!singularxx){
                thetaxxx=atan2(rotMatxx.at<float>(2,1), rotMatxx.at<float>(2,2));
                thetazxx=atan2(rotMatxx.at<float>(1,0), rotMatxx.at<float>(0,0));
            }else{
                thetaxxx=atan2(-rotMatxx.at<float>(1,2), rotMatxx.at<float>(1,1));
                thetazxx=0;
            }
            thetaxxx=thetaxxx*180/3.1415926;
            thetazxx=thetazxx*180/3.1415926;
            #endif
            thetayxx=atan(-rotMatxx.at<float>(2,0)/ syxx);
            thetayxx=thetayxx*180/3.1415926;
            float x=z2/ sin(theta)-z1/tan(theta); 
            #ifndef USE_IMAGE
            goal_x[0]=goal_x[1];
            goal_x[1]=goal_x[2];
            goal_x[2]=x;
            goal_z[0]=goal_z[1];
            goal_z[1]=goal_z[2];
            goal_z[2]=z1;
            goal_z3[0]=goal_z3[1];
            goal_z3[1]=goal_z3[2];
            goal_z3[2]=z3;
            goal_theta[0]=goal_theta[1];
            goal_theta[1]=goal_theta[2];
            goal_theta[2]=thetay;
            for(int i=0;i<3;i++)
            {
                temp_x[i]=goal_x[i];
                temp_z[i]=goal_z[i];
                temp_z3[i]=goal_z3[i];
                temp_theta[i]=goal_theta[i];
            }
            bubble_sort3(temp_x);
            bubble_sort3(temp_z);
            bubble_sort3(temp_z3);
            bubble_sort3(temp_theta);
            if(IMAGE_X == 640)
            {
                /*x=(temp_x[0]+temp_x[1]+temp_x[2])/3;
                z1=(temp_z[0]+temp_z[1]+temp_z[2])/3;
                thetay=(temp_theta[0]+temp_theta[1]+temp_theta[2])/3;*/
                x=temp_x[1];
                z1=temp_z[1];
                z3=temp_z3[1];
                thetay=temp_theta[1];
                //z1=z1*1.0407+79.16;
            }
            if(IMAGE_X == 1280)
            {
                x=temp_x[1];
                z1=temp_z[1];
                z3=temp_z3[1];
                thetay=temp_theta[1];
                //z1=z1*0.95538-46.366;//改6mm坐标之前
                //z1=z1*0.95371+52.551;//改6mm坐标之后
                //z1=z1*0.89764+94.093;//校正畸变之后的
                if(z1<5300)
                {
                    z1=z1*0.95533-54.918;
                }
                else
                    z1=z1*0.93118-87.098;
                    //z1=z1*0.95371+52.551;
                z3=z3*0.7948-262.98;
                //z3=z3*0.95371+52.551;
            }
            #endif
            //z1=z1*0.95538-46.366;
            //x=x-90;
			//cout << endl << "x:" << P_oc.ptr<float>(0)[0] << " y:" << P_oc.ptr<float>(0)[1] << " z:" << P_oc.ptr<float>(0)[2] << endl; 
            #ifdef TEST
            cout<<"goal_x:"<<temp_x[0]<<" "<<temp_x[1]<<" "<<temp_x[2]<<endl;
            cout<<"goal_z:"<<temp_z[0]<<" "<<temp_z[1]<<" "<<temp_z[2]<<endl;
            cout<<"goal_theta:"<<temp_theta[0]<<" "<<temp_theta[1]<<" "<<temp_theta[2]<<endl;
            cout << endl << "z1:" << z1 << "theta:" <<theta*180/pi<<"P_oc.ptr<float>(0)[0]:"<<P_oc.ptr<float>(0)[0]<<"x:" << x <<"z3:"<<z3<< " thetay:" << thetay <<endl; 
            outputfile << "time:"<<getCurrentTime()<<"z:"<<z1 <<"x:"<< x  <<"z3:"<<z3<<"theta:"<< thetay <<endl;
            #endif
            #ifdef USE_IMAGE
            outputfileline <<ImgName<<" "<<x<<endl;
            outputfilelinez3 <<ImgName<<" "<<z3<<endl;
            outputfileline00 <<ImgName<<" "<<P_oc.ptr<float>(0)[0]<<endl;
            #endif
//            TestSend(z3,z1);
		}
	}
	else 
	{
		z3 =0;
		z1=0;
		return 0;
	}
}


int SetPoint2D()
{
	if (POINTS_NUM == 4)
	{
		Point2f MidPoint;
		Point2f temp[POINTS_NUM];
		MidPoint.x = (goal_point[0].x + goal_point[1].x + goal_point[2].x + goal_point[3].x) / POINTS_NUM;
		MidPoint.y = (goal_point[0].y + goal_point[1].y + goal_point[2].y + goal_point[3].y) / POINTS_NUM;
		for (int i = 0; i < POINTS_NUM; i++)
		{
			if (goal_point[i].x<MidPoint.x&&goal_point[i].y < MidPoint.y)//Í¼Ïñ×óÉÏ
				temp[0] = goal_point[i];
			if (goal_point[i].x<MidPoint.x&&goal_point[i].y >MidPoint.y)//Í¼Ïñ×óÏÂ
				temp[1] = goal_point[i];
			if (goal_point[i].x>MidPoint.x&&goal_point[i].y < MidPoint.y)//Í¼ÏñÓÒÉÏ
				temp[2] = goal_point[i];
			if (goal_point[i].x>MidPoint.x&&goal_point[i].y > MidPoint.y)//Í¼ÏñÓÒÏÂ
				temp[3] = goal_point[i];
		}
		for (int i = 0; i < POINTS_NUM; i++)
		{
			Points2D[i] = temp[i];
		}
	}
	if (POINTS_NUM == 6)
	{
		int seq[POINTS_NUM]; 
		float mid_x = (goal_point[0].x + goal_point[1].x + goal_point[2].x + goal_point[3].x + goal_point[4].x + goal_point[5].x) / POINTS_NUM;
		float mid_y = (goal_point[0].y + goal_point[1].y + goal_point[2].y + goal_point[3].y + goal_point[4].y + goal_point[5].y) / POINTS_NUM;
		float min_x = 9999;
		float max_x = 0;
		for (int i = 0; i < POINTS_NUM; i++)
		{
			if (min_x > goal_point[i].x)
				min_x = goal_point[i].x;
			if (max_x < goal_point[i].x)
				max_x = goal_point[i].x;
		}
		float mid_left_x = (min_x + mid_x) / 2;
		float mid_right_x = (max_x + mid_x) / 2;

		for (int i = 0; i < POINTS_NUM; i++)
		{
			if (goal_point[i].y < mid_y&& goal_point[i].x < mid_left_x)//×óÉÏ
				seq[0] = i;
			if (goal_point[i].y > mid_y&& goal_point[i].x < mid_left_x)//×óÏÂ
				seq[1] = i;
			if (goal_point[i].y < mid_y&& goal_point[i].x > mid_left_x&& goal_point[i].x < mid_right_x)//ÖÐÉÏ
				seq[2] = i;
			if (goal_point[i].y > mid_y&& goal_point[i].x > mid_left_x&& goal_point[i].x < mid_right_x)//ÖÐÉÏ
				seq[3] = i;
			if (goal_point[i].y < mid_y&& goal_point[i].x > mid_right_x)//ÓÒÉÏ
				seq[4] = i;
			if (goal_point[i].y > mid_y&& goal_point[i].x > mid_right_x)//ÓÒÉÏ
				seq[5] = i;
		}
		Points2D[0] = goal_point[seq[0]];//×óÉÏ
		Points2D[1] = goal_point[seq[1]];//×óÏÂ
		Points2D[2] = goal_point[seq[2]];//ÖÐÉÏ
		Points2D[3] = goal_point[seq[3]];//ÖÐÏÂ
		Points2D_1[0] = goal_point[seq[2]];//ÖÐÉÏ
		Points2D_1[1] = goal_point[seq[3]];//ÖÐÏÂ
		Points2D_1[2] = goal_point[seq[4]];//ÓÒÉÏ
		Points2D_1[3] = goal_point[seq[5]];//ÓÒÏÂ

	}

	return 0;
}

#include "include/main.h"

Point2f goal_point[POINTS_NUM];
int get_flag;
extern Mat src_img ;
extern vector<cv::Point2f> Points2D;
extern vector<cv::Point2f> Points2D_1;
void bubble_sorty(vector<Point2f> &arr, int len)
{
	if (len > 1)
	{
		int i, j;
        for (i = 0; i < len - 1; i++)
            for (j = 0; j < len - 1 - i; j++)
				if (arr[j].y > arr[j + 1].y)
					swap(arr[j], arr[j + 1]);
	}
}
void bubble_sortx(vector<Point2f> &arr, int len)
{
	if (len > 1)
	{
		int i, j;
        for (i = 0; i < len - 1; i++)
            for (j = 0; j < len - 1 - i; j++)
				if (arr[j].x > arr[j + 1].x)
					swap(arr[j], arr[j + 1]);
	}
}

int ImageProcess(void)
{
    int nThresh = 30;
    Mat element = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat g_canny;
	Mat imgRGB;
	vector<vector<Point>> contours;
	vector<Vec4i> g_vHierarchy;
    Rect boundRect;
    RotatedRect minRect;
#ifdef SAVE_IMG
	char filename[20];
    time_t t = time(NULL);
	struct tm* timeInfo = localtime(&t);
	strftime(filename, 24, "%m%d_%H%M_%S", timeInfo); 
	strcat(filename, ".png");
	imwrite(filename, src_img);
#endif
#ifdef IMSHOW
	imshow("Ô­Í¼", src_img);
#endif
	cvtColor(src_img, src_img, COLOR_RGB2GRAY);
    if (POINTS_NUM == 4)
    {
        Point2f Point1;
        Point2f PointCenter;
        Point2f PointLeftupCent, PointRightupCent, PointRightdownCent, PointLeftdownCent;
        vector<cv::Point2f> Points;
        vector<cv::Point2f> PointsLeftup;
        vector<cv::Point2f> PointsRightup;
        vector<cv::Point2f> PointsRightdown;
        vector<cv::Point2f> PointsLeftdown;
        float k1, k, k2, b1, b2;
        int flag=0;
        for (int i = 1; (flag!=1)&&(i < (src_img.rows-1)); i++)
        {
            for (int j = 1; (flag!=1)&&(j < (src_img.cols-1)); j++)
            {
                if ((src_img.at<uchar>(i - 1, j - 1) > 245) && (src_img.at<uchar>(i - 1, j) > 245) && (src_img.at<uchar>(i - 1, j + 1) > 245) && (src_img.at<uchar>(i, j - 1) > 245) && (src_img.at<uchar>(i, j) > 245) && (src_img.at<uchar>(i, j + 1) > 245) && (src_img.at<uchar>(i + 1, j - 1) > 245) && (src_img.at<uchar>(i + 1, j) > 245) && (src_img.at<uchar>(i + 1, j + 1) > 245))
                {
                    Point1.x = j;
                    Point1.y = i;
                    flag=1;
                }
            }
        }
        cout<<"point1:"<<Point1<<endl;
        for (int i = 0; i < (src_img.rows - 1); i++)
        {
            for (int j = 0; j < (src_img.cols - 1); j++)
            {
                if(src_img.at<uchar>(i , j ) > 245)
                {
                    Points.push_back(Point(j,i));
                }
            }
        }
        cout<<"dengsize"<<Points.size()<<endl;
        if(Points.size()>100)
        {
            for (int o = 0; o < Points.size(); o++)
            {
                PointCenter.x = PointCenter.x + Points[o].x;
                PointCenter.y = PointCenter.y + Points[o].y;
            }
            PointCenter.x = PointCenter.x / Points.size();
            PointCenter.y = PointCenter.y / Points.size();
            cout<<"pointcenter:"<<PointCenter<<endl;
            if (PointCenter.x == Point1.x)
            {
                k = 5000;
            }
            else
            {
                k = (PointCenter.y- Point1.y) / (PointCenter.x - Point1.x);
            }
            if (k == 1)
            {
                for (int m = 0; m < Points.size(); m++)
                {
                    if ((Points[m].x < PointCenter.x) && (Points[m].y < PointCenter.y))
                    {
                        PointsLeftup.push_back(Points[m]);
                    }
                    else if ((Points[m].x > PointCenter.x) && (Points[m].y < PointCenter.y))
                    {
                        PointsRightup.push_back(Points[m]);
                    }
                    else if ((Points[m].x > PointCenter.x) && (Points[m].y > PointCenter.y))
                    {
                        PointsRightdown.push_back(Points[m]);
                    }
                    else if ((Points[m].x < PointCenter.x) && (Points[m].y > PointCenter.y))
                    {
                        PointsLeftdown.push_back(Points[m]);
                    }
                }
            }
            else
            {
                if (k == 5000)
                {
                    k2 = 1;
                    k1 = -1;
                }
                else
                {
                    k2 = (k-1) / (k+1);
                    k1 = (k + 1) / ( 1-k);
                }
                b1 = PointCenter.y - k1 * PointCenter.x;
                b2 = PointCenter.y - k2 * PointCenter.x;
                for (int p = 0; p < Points.size() ;p++)
                {
                    if ((Points[p].y < PointCenter.y) && (Points[p].x < ((Points[p].y - b1) / k1)) && (Points[p].x > ((Points[p].y - b2) / k2)))
                    {
                        PointsLeftup.push_back(Points[p]);
                    }
                    else if((Points[p].x > PointCenter.x) && (Points[p].y > (k1*Points[p].x+b1)) && (Points[p].y < (k2*Points[p].x + b2)))
                    {
                        PointsRightup.push_back(Points[p]);
                    }
                    else if ((Points[p].y > PointCenter.y) && (Points[p].x > ((Points[p].y - b1) / k1)) && (Points[p].x < ((Points[p].y - b2) / k2)))
                    {
                        PointsRightdown.push_back(Points[p]);
                    }
                    else if ((Points[p].x < PointCenter.x) && (Points[p].y < (k1*Points[p].x + b1)) && (Points[p].y > (k2*Points[p].x + b2)))
                    {
                        PointsLeftdown.push_back(Points[p]);
                    }
                }
            }
            cout<<"k:"<<k<<endl;
            cout<<"k1:"<<k1<<"k2"<<k2<<endl;
            cout<<"左上点数："<<PointsLeftup.size()<<endl;
            cout<<"右上点数："<<PointsRightup.size()<<endl;
            cout<<"右下点数："<<PointsRightdown.size()<<endl;
            cout<<"左下点数："<<PointsLeftdown.size()<<endl;
            if((PointsLeftup.size()>25)&&(PointsRightup.size()>25)&&(PointsRightdown.size()>25)&&(PointsLeftdown.size()>25))
            {
                for (int s = 0; s < PointsLeftup.size(); s++)
                {
                    PointLeftupCent.x = PointLeftupCent.x + PointsLeftup[s].x;
                    PointLeftupCent.y = PointLeftupCent.y + PointsLeftup[s].y;
                }
                PointLeftupCent.x = PointLeftupCent.x/ PointsLeftup.size();
                PointLeftupCent.y = PointLeftupCent.y /PointsLeftup.size();
                for (int t = 0; t < PointsRightup.size(); t++)
                {
                    PointRightupCent.x = PointRightupCent.x + PointsRightup[t].x;
                    PointRightupCent.y = PointRightupCent.y + PointsRightup[t].y;
                }
                PointRightupCent.x = PointRightupCent.x / PointsRightup.size();
                PointRightupCent.y = PointRightupCent.y / PointsRightup.size();
                for (int u = 0; u < PointsRightdown.size(); u++)
                {
                    PointRightdownCent.x = PointRightdownCent.x + PointsRightdown[u].x;
                    PointRightdownCent.y = PointRightdownCent.y + PointsRightdown[u].y;
                }
                PointRightdownCent.x = PointRightdownCent.x / PointsRightdown.size();
                PointRightdownCent.y = PointRightdownCent.y / PointsRightdown.size();
                for (int v = 0; v < PointsLeftdown.size(); v++)
                {
                    PointLeftdownCent.x = PointLeftdownCent.x + PointsLeftdown[v].x;
                    PointLeftdownCent.y = PointLeftdownCent.y + PointsLeftdown[v].y;
                }
                PointLeftdownCent.x = PointLeftdownCent.x / PointsLeftdown.size();
                PointLeftdownCent.y = PointLeftdownCent.y / PointsLeftdown.size();
                goal_point[0]=PointLeftupCent;
                goal_point[1]=PointRightupCent;
                goal_point[2]=PointRightdownCent;
                goal_point[3]=PointLeftdownCent;
                get_flag = true;
            }
            else get_flag = false;
            return 0;
        }
        get_flag = false;
        return 0;
    }
    if (POINTS_NUM == 6)
    {
        vector<cv::Point2f> Points;
        vector<cv::Point2f> Points1;
        vector<cv::Point2f> Points11;
        vector<cv::Point2f> Points12;
        vector<cv::Point2f> Points2;
        vector<cv::Point2f> Points21;
        vector<cv::Point2f> Points22;
        vector<cv::Point2f> Points3;
        vector<cv::Point2f> Points31;
        vector<cv::Point2f> Points32;
        int center;//中间点
        int first;
        int last;
        
        for (int i = 0; i < src_img.rows ; i++)
        {
            for (int j = 0; j < src_img.cols ; j++)
            {
                if(src_img.at<uchar>(i , j ) > 200)
                {
                    Points.push_back(Point(j,i));
                }
            }
        }
        #ifdef TEST
        cout<<"pointsnumber:"<<Points.size()<<endl;
        #endif

        #ifdef IMAGE_1280
            if(Points.size()>0)
            {
                bubble_sortx(Points, Points.size());
                center=int(Points.size()/2);
                first=int(Points.size()/6);
                last=Points.size()-first;
                for(int i=0;i<Points.size();i++)
                {
                    //cout<<Points[i].x<<endl;
                    if((Points[i].x<(Points[center].x+Points[first].x)/2)&&(Points[i].y<(Points[first].y+250))&&(Points[i].x>(Points[first].x-100))&&((Points[center].x-Points[first].x)>20)&&((Points[last].x-Points[center].x)>20))
                    {
                        Points1.push_back(Points[i]);
                    }
                    else if((Points[i].x>(Points[center].x+Points[first].x)/2)&&(Points[i].x<(Points[center].x+Points[last].x)/2)&&(Points[i].y<(Points[first].y+250))&&((Points[center].x-Points[first].x)>20)&&((Points[last].x-Points[center].x)>20))
                    {
                        Points2.push_back(Points[i]);
                    }
                    else if((Points[i].x>(Points[center].x+Points[last].x)/2)&&(Points[i].x<(Points[last].x+100))&&(Points[i].y<(Points[first].y+250))&&((Points[center].x-Points[first].x)>20)&&((Points[last].x-Points[center].x)>20))
                    {
                        Points3.push_back(Points[i]);
                    }
                }
                #ifdef TEST
                cout<<"Points1size:"<<Points1.size()<<"Points2size:"<<Points2.size()<<"Points3size:"<<Points3.size()<<endl;
                #endif
                if((Points1.size()>0)&&(Points2.size()>0)&&(Points3.size()>0))
                {
                    int first1,first2,first3,last1,last2,last3;
                    first1=int(Points1.size()/3);
                    first2=int(Points2.size()/6);
                    first3=int(Points3.size()/3);
                    last1=Points1.size()-first1;
                    last2=Points2.size()-first2;
                    last3=Points3.size()-first3;
                    bubble_sorty(Points1, Points1.size());
                    bubble_sorty(Points2, Points2.size());
                    bubble_sorty(Points3, Points3.size());
                    for(int j=0;j<Points1.size();j++)
                    {
//                        cout<<"points1y:"<<Points1[j].y<<endl;
                        if((Points1[last1].y-Points1[first1].y)>20)
                        {
                            if(Points1[j].y<(Points1[first1].y+Points1[last1].y)/2)
                            {
                                Points11.push_back(Points1[j]);
                            }
                            else
                            {
                                Points12.push_back(Points1[j]);
                            }
                        }
                        
                    }
                    for(int l=0;l<Points2.size();l++)
                    {
                        if((Points2[last2].y-Points2[first2].y)>15)
                        {
                            if(Points2[l].y<(Points2[first2].y+Points2[last2].y)/2)
                            {
                                Points21.push_back(Points2[l]);
                            }
                            else
                            {
                                Points22.push_back(Points2[l]);
                            }
                        }
                    }
                    for(int m=0;m<Points3.size();m++)
                    {
                        if((Points3[last3].y-Points3[first3].y)>10)
                        {
                            if(Points3[m].y<(Points3[first3].y+Points3[last3].y)/2)
                            {
                                Points31.push_back(Points3[m]);
                            }
                            else
                            {
                                Points32.push_back(Points3[m]);
                            }
                        }
                    }
                    if((Points11.size()>0)&&(Points21.size()>0)&&(Points31.size()>0)&&(Points12.size()>0)&&(Points22.size()>0)&&(Points32.size()>0))
                    {
                        Points2D.resize(4);
                        Points2D_1.resize(4);
                        for(int t=0;t<4;t++)
                        {
                            Points2D[t].x=0;
                            Points2D[t].y=0;
                            Points2D_1[t].x=0;
                            Points2D_1[t].y=0;
                        }
                        for(int n=0;n<Points11.size();n++)
                        {
                            Points2D[0].x+=Points11[n].x;
                            Points2D[0].y+=Points11[n].y;
                        }
                        Points2D[0].x=Points2D[0].x/Points11.size();
                        Points2D[0].y=Points2D[0].y/Points11.size();
                        for(int o=0;o<Points12.size();o++)
                        {
                            Points2D[1].x+=Points12[o].x;
                            Points2D[1].y+=Points12[o].y;
                        }
                        Points2D[1].x=Points2D[1].x/Points12.size();
                        Points2D[1].y=Points2D[1].y/Points12.size();
                        for(int p=0;p<Points21.size();p++)
                        {
                            Points2D[2].x+=Points21[p].x;
                            Points2D[2].y+=Points21[p].y;
                        }
                        Points2D[2].x=Points2D[2].x/Points21.size();
                        Points2D[2].y=Points2D[2].y/Points21.size();
                        for(int q=0;q<Points22.size();q++)
                        {
                            Points2D[3].x+=Points22[q].x;
                            Points2D[3].y+=Points22[q].y;
                        }
                        Points2D[3].x=Points2D[3].x/Points22.size();
                        Points2D[3].y=Points2D[3].y/Points22.size();
                        Points2D_1[0]=Points2D[2];
                        Points2D_1[1]=Points2D[3];
                        for(int r=0;r<Points31.size();r++)
                        {
                            Points2D_1[2].x+=Points31[r].x;
                            Points2D_1[2].y+=Points31[r].y;
                        }
                        Points2D_1[2].x=Points2D_1[2].x/Points31.size();
                        Points2D_1[2].y=Points2D_1[2].y/Points31.size();
                        for(int s=0;s<Points32.size();s++)
                        {
                            Points2D_1[3].x+=Points32[s].x;
                            Points2D_1[3].y+=Points32[s].y;
                        }
                        Points2D_1[3].x=Points2D_1[3].x/Points32.size();
                        Points2D_1[3].y=Points2D_1[3].y/Points32.size();
                        get_flag = true;
#ifdef TEST
                        Mat imgRGB;
                        cvtColor(src_img, imgRGB, COLOR_GRAY2RGB);
                        for(int n=0;n<4;n++)
                        {
                            circle(imgRGB,Points2D[n],1,Scalar(0,0,255),-1,8);
                        }
                        circle(imgRGB,Points2D_1[2],1,Scalar(0,0,255),-1,8);
                        circle(imgRGB,Points2D_1[3],1,Scalar(0,0,255),-1,8);
#ifdef IMSHOW
                        imshow("pointimg",imgRGB);
#endif
#endif
                        //GetLocation();
                    }
                    else
                        get_flag = false;
                    //return 0;
                }
                else
                    get_flag = false;
                //return 0;
            }
            else
                get_flag = false;
        #endif

        #ifdef IMAGE_640
            if(Points.size()>0)
                {
                    bubble_sortx(Points, Points.size());
                    center=int(Points.size()/2);
                    first=int(Points.size()/6);
                    last=Points.size()-first;
                    for(int i=0;i<Points.size();i++)
                    {
                        //cout<<Points[i].x<<endl;
                        if((Points[i].x<(Points[center].x+Points[first].x)/2)&&(Points[i].y<(Points[first].y+200))&&(Points[i].x>(Points[first].x-100))&&((Points[center].x-Points[first].x)>20)&&((Points[last].x-Points[center].x)>20))
                        {
                            Points1.push_back(Points[i]);
                        }
                        else if((Points[i].x>(Points[center].x+Points[first].x)/2)&&(Points[i].x<(Points[center].x+Points[last].x)/2)&&(Points[i].y<(Points[first].y+200))&&((Points[center].x-Points[first].x)>20)&&((Points[last].x-Points[center].x)>20))
                        {
                            Points2.push_back(Points[i]);
                        }
                        else if((Points[i].x>(Points[center].x+Points[last].x)/2)&&(Points[i].x<(Points[last].x+100))&&(Points[i].y<(Points[first].y+200))&&((Points[center].x-Points[first].x)>20)&&((Points[last].x-Points[center].x)>20))
                        {
                            Points3.push_back(Points[i]);
                        }
                    }
                    #ifdef TEST
                    cout<<"Points1size:"<<Points1.size()<<"Points2size:"<<Points2.size()<<"Points3size:"<<Points3.size()<<endl;
                    #endif
                    if((Points1.size()>0)&&(Points2.size()>0)&&(Points3.size()>0))
                    {
                        int first1,first2,first3,last1,last2,last3;
                        first1=int(Points1.size()/6);
                        first2=int(Points2.size()/6);
                        first3=int(Points3.size()/6);
                        last1=Points1.size()-first1;
                        last2=Points2.size()-first2;
                        last3=Points3.size()-first3;
                        bubble_sorty(Points1, Points1.size());
                        bubble_sorty(Points2, Points2.size());
                        bubble_sorty(Points3, Points3.size());
                        for(int j=0;j<Points1.size();j++)
                        {
                            //cout<<"points1y:"<<Points1[j].y<<endl;
                            if((Points1[last1].y-Points1[first1].y)>20)
                            {
                                if(Points1[j].y<(Points1[first1].y+Points1[last1].y)/2)
                                {
                                    Points11.push_back(Points1[j]);
                                }
                                else
                                {
                                    Points12.push_back(Points1[j]);
                                }
                            }
                            
                        }
                        for(int l=0;l<Points2.size();l++)
                        {
                            //cout<<"points2y:"<<Points2[l].y<<endl;
                            if((Points2[last2].y-Points2[first2].y)>15)
                            {
                                if(Points2[l].y<(Points2[first2].y+Points2[last2].y)/2)
                                {
                                    Points21.push_back(Points2[l]);
                                }
                                else
                                {
                                    Points22.push_back(Points2[l]);
                                }
                            }
                        }
                        for(int m=0;m<Points3.size();m++)
                        {
                            //cout<<"points3y:"<<Points3[m].y<<endl;
                            if((Points3[last3].y-Points3[first3].y)>10)
                            {
                                if(Points3[m].y<(Points3[first3].y+Points3[last3].y)/2)
                                {
                                    Points31.push_back(Points3[m]);
                                }
                                else
                                {
                                    Points32.push_back(Points3[m]);
                                }
                            }
                        }
                        if((Points11.size()>0)&&(Points21.size()>0)&&(Points31.size()>0)&&(Points12.size()>0)&&(Points22.size()>0)&&(Points32.size()>0))
                        {
                            Points2D.resize(4);
                            Points2D_1.resize(4);
                            for(int t=0;t<4;t++)
                            {
                                Points2D[t].x=0;
                                Points2D[t].y=0;
                                Points2D_1[t].x=0;
                                Points2D_1[t].y=0;
                            }
                            for(int n=0;n<Points11.size();n++)
                            {
                                Points2D[0].x+=Points11[n].x;
                                Points2D[0].y+=Points11[n].y;
                            }
                            Points2D[0].x=Points2D[0].x/Points11.size();
                            Points2D[0].y=Points2D[0].y/Points11.size();
                            for(int o=0;o<Points12.size();o++)
                            {
                                Points2D[1].x+=Points12[o].x;
                                Points2D[1].y+=Points12[o].y;
                            }
                            Points2D[1].x=Points2D[1].x/Points12.size();
                            Points2D[1].y=Points2D[1].y/Points12.size();
                            for(int p=0;p<Points21.size();p++)
                            {
                                Points2D[2].x+=Points21[p].x;
                                Points2D[2].y+=Points21[p].y;
                            }
                            Points2D[2].x=Points2D[2].x/Points21.size();
                            Points2D[2].y=Points2D[2].y/Points21.size();
                            for(int q=0;q<Points22.size();q++)
                            {
                                Points2D[3].x+=Points22[q].x;
                                Points2D[3].y+=Points22[q].y;
                            }
                            Points2D[3].x=Points2D[3].x/Points22.size();
                            Points2D[3].y=Points2D[3].y/Points22.size();
                            Points2D_1[0]=Points2D[2];
                            Points2D_1[1]=Points2D[3];
                            for(int r=0;r<Points31.size();r++)
                            {
                                Points2D_1[2].x+=Points31[r].x;
                                Points2D_1[2].y+=Points31[r].y;
                            }
                            Points2D_1[2].x=Points2D_1[2].x/Points31.size();
                            Points2D_1[2].y=Points2D_1[2].y/Points31.size();
                            for(int s=0;s<Points32.size();s++)
                            {
                                Points2D_1[3].x+=Points32[s].x;
                                Points2D_1[3].y+=Points32[s].y;
                            }
                            Points2D_1[3].x=Points2D_1[3].x/Points32.size();
                            Points2D_1[3].y=Points2D_1[3].y/Points32.size();
                            get_flag = true;
#ifdef TEST
                            Mat imgRGB;
                            cvtColor(src_img, imgRGB, COLOR_GRAY2RGB);
                            for(int n=0;n<4;n++)
                            {
                                circle(imgRGB,Points2D[n],1,Scalar(0,0,255),-1,8);
                            }
                            circle(imgRGB,Points2D_1[2],1,Scalar(0,0,255),-1,8);
                            circle(imgRGB,Points2D_1[3],1,Scalar(0,0,255),-1,8);
#ifdef IMSHOW
                            imshow("pointimg",imgRGB);
#endif
#endif
                            //GetLocation();
                        }
                        else
                            get_flag = false;
                        //return 0;
                    }
                    else
                        get_flag = false;
                    //return 0;
            }
                else
                    get_flag = false;
        #endif
        #ifdef TEST
        cout<<"points11number:"<<Points11.size()<<"points12number:"<<Points12.size()<<"points21number:"<<Points21.size()<<"points22number:"<<Points22.size()<<"points31number:"<<Points31.size()<<"points32number:"<<Points32.size()<<endl;
        #endif
        return 0;
    }
}
float GetDistance(CvPoint pointO, CvPoint pointA)
{
	float distance;
	distance = powf((pointO.x - pointA.x), 2) + powf((pointO.y - pointA.y), 2);
	distance = sqrtf(distance);
	return distance;
}

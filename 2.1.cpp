#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include <cv.h>
#include<vector>
#include <string>

using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
     RNG rng(0x1234);
     int rows,cols,cannels;
    int t1,t2;
    int ovr;
    Mat gaus,gaus1;
  if( argc < 2 )
  {
    std::cout << "need file name on command line!"
        << std::endl;
    return -1;
  }

  cv::VideoCapture cap( argv[1] );
  if( !cap.isOpened() )
  {
    std::cout << "error openning video file"
        << std::endl;
    return -1;
  }

  std::cout << "Video file " << argv[1] <<
      " is opened!" << std::endl;

  cv::Mat frame;
  int cnt = 0;
  while(1)
  {
    cap >> frame;

    if( frame.empty() )
    {

      std::cout << "ahh, all frames processed!"
          << std::endl;
      break;
    }
    else
    {
        gaus=frame.clone();

        rows=frame.rows;
        cols=frame.cols;
        cannels=3;
        ovr=(int)rng.gaussian(100);
        for(int i=0;i<rows;i++)
        {
            uchar*p =gaus.ptr<uchar>(i);
            for(int j=0;j<cols;j++)
            {
                if((int)rng.gaussian(100)%100>=98)
                {
                    p[j*cannels+0]=255;
                    p[j*cannels+1]=255;
                    p[j*cannels+2]=255;
                }
                if((int)rng.gaussian(100)%100>=98)
                {
                    p[j*cannels+0]=0;
                    p[j*cannels+1]=0;
                    p[j*cannels+2]=0;
                }

            }
        }
        int tec;
        if(ovr%100>90)
        {
            tec=(int)rng.uniform(0,20);
            for(int i=0;i<rows-tec;i++)
            {
                uchar*p =gaus.ptr<uchar>(i);
                uchar*p1=gaus.ptr<uchar>(i+tec);
                for(int j=0;j<cols;j++)
                {
                    for(int k=0;k<3;k++)
                    {
                        p[j*cannels+k]=p1[j*cannels+k];

                    }
                }
            }
            for(int i=rows-tec;i<rows;i++)
            {
                uchar*p =gaus.ptr<uchar>(i);
                for(int j=0;j<cols;j++)
                {
                    for(int k=0;k<3;k++)
                    {
                        p[j*cannels+k]=0;

                    }
                }
            }
        }
        if(ovr%100<7)
        {
            tec=(int)rng.uniform(0,20);
            for(int i=rows-1;i>tec;i--)
            {
                uchar*p =gaus.ptr<uchar>(i);
                uchar*p1=gaus.ptr<uchar>(i-tec);
                for(int j=0;j<cols;j++)
                {
                    for(int k=0;k<3;k++)
                    {
                        p[j*cannels+k]=p1[j*cannels+k];

                    }
                }
            }
            for(int i=0;i<tec;i++)
            {
                uchar*p =gaus.ptr<uchar>(i);
                for(int j=0;j<cols;j++)
                {
                    for(int k=0;k<3;k++)
                    {
                        p[j*cannels+k]=0;

                    }
                }
            }
        }
        cvtColor( gaus,gaus1, COLOR_BGR2GRAY );


        imshow( "Original", frame);
        imshow("Gaus",gaus1);
        waitKey(33);


    }
    cnt++;
  }
  std::cout << "frames count " << cnt << std::endl;
  return 0;
}

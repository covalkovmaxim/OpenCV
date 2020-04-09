#include <opencv2/core/core.hpp>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

using namespace cv;
using namespace std;
int main()
{
    Mat img=imread("./cat.jpeg", IMREAD_COLOR);
    Mat ch[3];
    split(img,ch);
     imshow( "Display window",ch[0]);
     waitKey();
     imshow( "Display window",ch[1]);
     waitKey();
     imshow( "Display window",ch[2]);
     waitKey();
    return 0;
}

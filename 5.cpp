#include <opencv2/core/core.hpp>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include<vector>
#include<iterator>

using namespace std;
using namespace cv;

void plotCon(Mat img,vector<vector<Point2i>> contours);
void print_tree(const vector<Vec4i>& hierarchy,int s);
int main()
{
    Mat im0,im,bin,img0,img,con;
    img0 = imread("new1.jpg", IMREAD_COLOR);
    resize(img0,img,Size(img0.cols*0.2,img0.rows*0.2),0,0,CV_INTER_LINEAR);
    printf("%d %d\n\n\n",img.cols,img.rows);
    cvtColor(img,im,COLOR_BGR2GRAY);
    threshold(im, bin, 130, 255, THRESH_BINARY_INV);
    int rows,cols;
    int key=0;
    //printf("rrrrrrrrrrrrr\n");
    rows=bin.rows;cols=bin.cols;
    for(int k=0;k<100;k++)
    {
    for(int i=1;i<rows-1;i++)
    {
        uchar*p =bin.ptr<uchar>(i);
        uchar*p1 =bin.ptr<uchar>(i-1);
        uchar*p2 =bin.ptr<uchar>(i+1);
        for(int j=1;j<cols-1;j++)
        {
            key=0;
            if(p1[j-1]==255) key++;
            if(p1[j]==255) key++;
            if(p1[j+1]==255) key++;
            if(p2[j-1]==255) key++;
            if(p2[j]==255) key++;
            if(p2[j+1]==255) key++;
            if(p[j-1]==255) key++;
            if(p[j+1]==255) key++;
            if(key>=5)
            {
                p[j]=255;
            }
            else
            {
                if(key<=3)
                {
                    p[j]=0;
                }
            }
        }
    }

    }

    namedWindow("Display window",WINDOW_AUTOSIZE);
    imshow( "Display window", bin );
    vector<vector<Point>> aprox;
    vector<vector<Point2i>> contours;
    vector<Vec4i> hierarchy;
    findContours(bin,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    cout << contours.size() << endl;
    //drawContours(con,contours,,Scalar(0,100,200),1);
    //imshow("Contours",con);
   /* for(int i=0;i<contours.size();i++)
    {
        printf("%d\n\n",i);
        for(int j=0;j<contours[i].size();j++)
        {
            printf("%d %d\n",contours[i][j].x,contours[i][j].y);
        }
        printf("\n");
    }*/
    plotCon(img,contours);
    imshow("1",img);
    findContours(bin,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);
    //print_tree(hierarchy,0);
    int cntrs=hierarchy.size();
    //printf("%d\n",cntrs);
    //cout << "[ ";
    for(int i=0;i<cntrs &&i!=-1;i=hierarchy[i][0])
    {

        const Vec4i & data=hierarchy[i];
        print_tree(hierarchy,data[2]);

        printf("\n");
    }
    printf("\n");
    waitKey(0);
    return 0;
}
void plotCon(Mat img,vector<vector<Point2i>> contours)
{
 for(int i=0;i<contours.size();i++)
 {
     for(int j=0;j<contours[i].size();j++)
     {
          uchar*p =img.ptr<uchar>(contours[i][j].y-1);
          p[(contours[i][j].x-1)*3+0]=0;
          p[(contours[i][j].x-1)*3+1]=0;
          p[(contours[i][j].x-1)*3+2]=255;

          p[contours[i][j].x*3+0]=0;
          p[contours[i][j].x*3+1]=0;
          p[contours[i][j].x*3+2]=255;

          p[(contours[i][j].x+1)*3+0]=0;
          p[(contours[i][j].x+1)*3+1]=0;
          p[(contours[i][j].x+1)*3+2]=255;

          p =img.ptr<uchar>(contours[i][j].y);
          p[(contours[i][j].x-1)*3+0]=0;
          p[(contours[i][j].x-1)*3+1]=0;
          p[(contours[i][j].x-1)*3+2]=255;

          p[contours[i][j].x*3+0]=0;
          p[contours[i][j].x*3+1]=0;
          p[contours[i][j].x*3+2]=255;

          p[(contours[i][j].x+1)*3+0]=0;
          p[(contours[i][j].x+1)*3+1]=0;
          p[(contours[i][j].x+1)*3+2]=255;

          p =img.ptr<uchar>(contours[i][j].y+1);
          p[(contours[i][j].x-1)*3+0]=0;
          p[(contours[i][j].x-1)*3+1]=0;
          p[(contours[i][j].x-1)*3+2]=255;

          p[contours[i][j].x*3+0]=0;
          p[contours[i][j].x*3+1]=0;
          p[contours[i][j].x*3+2]=255;

          p[(contours[i][j].x+1)*3+0]=0;
          p[(contours[i][j].x+1)*3+1]=0;
          p[(contours[i][j].x+1)*3+2]=255;
     }
 }
}
void print_tree(const vector<Vec4i>& hierarchy,int s)
{
    int cntrs=hierarchy.size();
    //printf("%d\n",cntrs);
    int i;
    cout << "[ ";
    for(i=s;i<cntrs &&i!=-1;i=hierarchy[i][0])
    {
        if(i!=s)
        {
            cout << ",";
        }
        cout << " ";
        const Vec4i & data=hierarchy[i];
        print_tree(hierarchy,data[2]);
    }
    if(i!=s)
    {
        cout << " ";
    }
    cout << " ]";
}

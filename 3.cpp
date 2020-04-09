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
int main()
{
    Mat im0,im,bin;
    im0 = imread("figure.jpg", IMREAD_GRAYSCALE);
    resize(im0,im,Size(im0.cols*0.1,im0.rows*0.1),0,0,CV_INTER_LINEAR);

    threshold(im, bin, 98, 255, THRESH_BINARY );
    imshow( "Display window", bin );
    int rows,cols;
    int key=0;
    printf("rrrrrrrrrrrrr\n");
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
            if(p1[j-1]==0) key++;
            if(p1[j]==0) key++;
            if(p1[j+1]==0) key++;
            if(p2[j-1]==0) key++;
            if(p2[j]==0) key++;
            if(p2[j+1]==0) key++;
            if(p[j-1]==0) key++;
            if(p[j+1]==0) key++;
            if(key>=5)
            {
                p[j]=0;
            }
            else
            {
                if(key<=1)
                {
                    p[j]=255;
                }
            }
        }
    }
    }
    printf("rrrrrrrrrrrrr\n");
    imshow( "Better", bin );
    int num=0,num1=0,num2=0,i0,j0,num_loc=0;
    int key0=1;
    while (key0!=0)
    {
        key0=0;
        for(int i=0;i<rows-1;i++)
        {
            uchar*p =bin.ptr<uchar>(i);
            for(int j=1;j<cols-1;j++)
            {
                if(p[j]==0)
                {
                    i0=i;j0=j;key0=1; num2=1;num1=0;num++;num_loc=1;p[j]=num*20; goto lh;
                }
            }
        }
        lh:
         while(num_loc!=0)
         {
             num_loc=0;
             for(int i=1;i<rows-1;i++)
             {
                 uchar*p =bin.ptr<uchar>(i);
                 uchar*p1 =bin.ptr<uchar>(i-1);
                 uchar*p2 =bin.ptr<uchar>(i+1);
                 for(int j=1;j<cols-1;j++)
                 {
                     if(p[j]==num*20)
                     {
                         if(p1[j-1]==0) {num_loc++;p1[j-1]=num*20;}
                         if(p1[j]==0) {num_loc++;p1[j]=num*20;}
                         if(p1[j+1]==0) {num_loc++;p1[j+1]=num*20;}
                         if(p2[j-1]==0) {num_loc++;p2[j-1]=num*20;}
                         if(p2[j]==0) {num_loc++;p2[j]=num*20;}
                         if(p2[j+1]==0) {num_loc++;p2[j+1]=num*20;}
                         if(p[j-1]==0) {num_loc++;p[j-1]=num*20;}
                         if(p[j+1]==0) {num_loc++;p[j+1]=num*20;}
                     }
                 }
             }
             num2=num1;num1+=num_loc;
         }

    }
     printf("rrrrrrrrrrrrr\n");
    for(int k=0;k<num;k++)
    {
        num1=0;
        for(int i=0;i<rows;i++)
        {
          uchar*p =bin.ptr<uchar>(i);
          for(int j=0;j<cols;j++)
          {
              if(p[j]==k*20)
              {
                  num1++;
              }
          }
        }
        if(num1<40)
        {
            for(int i=0;i<rows;i++)
            {
              uchar*p =bin.ptr<uchar>(i);
              for(int j=0;j<cols;j++)
              {
                  if(p[j]==k*20)
                  {
                      p[j]=255;
                  }
              }
            }
        }
    }
    //imshow( "Better2", bin );

    set<int> res;
    num1=1;
    for(int i=0;i<rows-1;i++)
    {
        uchar*p =bin.ptr<uchar>(i);
        for(int j=0;j<cols;j++)
        {
           if(p[j]!=255)
           {
               if(res.find(p[j])==res.end())
               {
                   res.insert(p[j]);
                   num1++;
               }
           }
        }
    }
    for(set<int>::iterator it=res.begin();it!=res.end();it++)
    {
        printf("%d ",*(it));
    }
    printf("\n");
    printf("Number of components:%d\n",num1);
    Mat*obj;
    obj=new Mat[res.size()];
    num1=0;
    char word[256];

    for(set<int>::iterator it=res.begin();it!=res.end();it++)
    {
        obj[num1]=bin!=*it;
        num1++;
        sprintf(word,"Conponent%d",num1);
        imshow(word,obj[num1-1]);
    }
    Moments*mom;
    Moments*humom;
    mom=new Moments[res.size()];
    humom=new Moments[res.size()];
    num=res.size();
    Moments*hm;
    hm=new Moments[7];
   double ar[7];
   double asv=0.;
    for(int i=0;i<num;i++)
    {
        mom[i]=moments( obj[i], false);
        //printf("%d %f %f\n",i,mom[i].m00,mom[i].m01,);
        //HuMoments( humom[i], obj[i]);
        //printf("%d %f %f\n",i,mom[i].m00,humom[i].m01);
        HuMoments(mom[i],ar);
        printf("%d: ",i);
        asv=0.;
        for(int j=0;j<7;j++)
        {
            asv+=log(fabs(ar[j]))*log(fabs(ar[j]));
        }
        printf("%f\n",sqrt(asv));
    }


    imshow( "Better2", bin );


    printf("num=%d\n",num);
    waitKey(0);
    return 0;
}

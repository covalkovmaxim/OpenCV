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
    Mat im0,im,bin,img0,img;
    img0 = imread("nikita.jpg", IMREAD_COLOR);
    resize(img0,img,Size(img0.cols*0.5,img0.rows*0.5),0,0,CV_INTER_LINEAR);

    im0 = imread("nikita.jpg", IMREAD_GRAYSCALE);
    resize(im0,im,Size(im0.cols*0.5,im0.rows*0.5),0,0,CV_INTER_LINEAR);
    threshold(im, bin, 98, 255, THRESH_BINARY );
    //imshow( "Display window", bin );
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
    //imshow( "Better", bin );
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
    double*ark;
    ark=new double[res.size()];
    obj=new Mat[res.size()];
    num1=0;
    char word[256];

    for(set<int>::iterator it=res.begin();it!=res.end();it++)
    {
        obj[num1]=bin==*it;
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
    double**wer;
    wer=new double* [num];
    for(int i=0;i<num;i++)
    {
        wer[i]=new double[7];
    }
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
            wer[i][j]=ar[j];
            asv+=log(fabs(ar[j]))*log(fabs(ar[j]));
            ///asv+=fabs(ar[j])*fabs(ar[j]);
        }
        ark[i]=sqrt(asv);
       // printf("%f\n",sqrt(asv));
    }
    Mat cur; double cr;
    /*for(int i=0;i<num-1;i++)
    {
        for(int j=i+1;j<num;j++)
        {
            if(ark[i]>ark[j])
            {
                cr=ark[i];
                ark[i]=ark[j];
                ark[j]=cr;

                cur=obj[i];
                obj[i]=obj[j];
                obj[j]=cur;
            }
        }
    }*/
    int index=1;
    int *ind;
    int sab=0;
    ind=new int[num];
    for(int i=0;i<num;i++)
    {
        ind[i]=-1;
    }
    ind[0]=1;
    asv=0.;
    printf("\n");
    for(int i=0;i<num;i++)
    {
        for(int j=0; j<num;j++)
        {
            asv=0.;
            for(int ii=0;ii<7;ii++)
            {
                asv+=fabs(log(fabs(wer[i][ii]))-log(fabs(wer[j][ii])));
            }
           printf("%f ",asv);
        }
        printf("\n");
    }
    for(int i=0;i<num;i++)
    {
        if(ind[i]==-1)
        {

            for(int j=0;j<num;j++)
            {
                asv=0.;
                for(int ii=0;ii<7;ii++)
                {
                    //asv+=fabs(wer[i][ii]-wer[j][ii]);
                     asv+=fabs(log(fabs(wer[i][ii]))-log(fabs(wer[j][ii])));
                }
                //asv=sqrt(asv);
                printf("%d %d %f\n",i,j, asv);
                if(ind[j]>-1&&asv<10.)
                {
                    ind[i]=ind[j];
                    break;
                }

            }
        }
        if(ind[i]==-1)
        {
            index++;
            ind[i]=index;
        }
    }
    int x=0,y=0;
    char text[256];
    for(int i=0;i<num;i++)
    {
        x=y=0;index=0;
        for(int i1=0;i1<rows;i1++)
        {
            uchar*p =obj[i].ptr<uchar>(i1);
            for(int i2=0;i2<cols;i2++)
            {
               if(p[i2]==255)
               {
                   index++;
                   x+=i2;
                   y+=i1;
               }
            }
        }
        x=x/index;
        y=y/index;
        Point textOrg(x-7,y+7);
        int fontFace=FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontSize=1;
        Scalar color(256,256,256);
        sprintf(text,"%d",ind[i]);
        putText(img,text,textOrg,fontFace,fontSize,color);

    }
   // imshow( "Better2", bin );
    imshow("Classification",img);

    printf("num=%d\n",num);
    waitKey(0);
    for(int i=0;i<num;i++)
    {
        delete[] wer[i];
    }
    delete[]wer;
    delete[]ark;
    delete[]mom;
    delete[]humom;
    delete[]hm;
    delete[]obj;
    delete[]ind;
    return 0;
}

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
        RNG rng(0x1234);
        Point pt,textOrg(30,50);
        int num=0;
        char text[256];
        sprintf(text,"WINS: 00%d",num);
        Mat fon,ship,ship_i,result,ship0;//Создание объекта под изображение.

        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        Scalar color(200,100,50);

        int time=200;
        //Считывание изображения из файла.
        fon = imread("./fon1.png", IMREAD_COLOR);//и
        //инициализация им матрицы img.
        ship0=imread("./ship2.jpg",IMREAD_COLOR);
        flip(ship0,ship0,1);
         pt.x=rng.uniform(int(fon.cols*0.1),int(fon.cols*0.9));
         pt.y=400;

        resize(ship0,ship,Size(ship0.cols*0.4,ship0.rows*0.4),0,0,CV_INTER_LINEAR);
        Rect roi( 0, 223, ship.cols, ship.rows);

        result=fon.clone();
        flip(ship,ship_i,1);
         ship.copyTo(result(roi));

         circle(result,pt,7,Scalar(70,30,100),-1);
          putText(result, text, textOrg, fontFace, fontScale,color);
         imshow( "Display window", result );
        char g;
        int x=0;
        for(int i=0;1;i++)
        {
             printf("%d\n",i);
            if(i<200)
            {

                time=200-i;
                imshow( "Display window", result );
            }
            else
            {
                i=0; time=200;
                pt.x=rng.uniform(int(fon.cols*0.1),int(fon.cols*0.9));
                pt.y=400;
                imshow( "Display window", result );
            }
            g=waitKey();
            if(g=='d')
            {
                if(x<=fon.rows-10)
                {
                    x+=10;
                }
                if(pt.x-30>=x&&pt.x<=x+145)
                {
                    num++;
                    if(num/100>=1)
                    {
                        sprintf(text,"WINS:%d       Time:%d:%d",num,time/100,time%100);
                    }
                    else
                    {
                        if(num/10>=1)
                        {
                            sprintf(text,"WINS:0%d       Time:%d:%d",num,time/100,time%100);
                        }
                        else
                        {
                             sprintf(text,"WINS:0%d       Time:%d:%d",num,time/100,time%100);
                        }
                    }
                    pt.x=rng.uniform(int(fon.cols*0.1),int(fon.cols*0.9));
                    pt.y=400;
                }
              Rect  roi( x, 223, ship.cols, ship.rows);
                result=fon.clone();
                ship.copyTo(result(roi));
                circle(result,pt,7,Scalar(10,40,50),-1);
                putText(result, text, textOrg, fontFace, fontScale,color);
                imshow( "Display window", result );
            }
            if(g=='a')
            {
            //    circle(result,pt,7,Scalar(70,30,100),-1);
                if(x>=10)
                {
                    x-=10;
                }
                if(pt.x-30>=x&&pt.x<=x+145)
                {     
                    num++;
                    if(num/100>=1)
                    {
                         sprintf(text,"WINS:%d       Time:%d:%d",num,time/100,time%100);
                    }
                    else
                    {
                        if(num/10>=1)
                        {
                             sprintf(text,"WINS:%0d       Time:%d:%d",num,time/100,time%100);
                        }
                        else
                        {
                             sprintf(text,"WINS:00%d       Time:%d:%d",num,time/100,time%100);
                        }
                    }
                    pt.x=rng.uniform(int(fon.cols*0.1),int(fon.cols*0.9));
                    pt.y=400;
                }
               Rect roi( x, 223, ship.cols, ship.rows);
                result=fon.clone();
                ship_i.copyTo(result(roi));
                circle(result,pt,7,Scalar(10,40,50),-1);
                putText(result, text, textOrg, fontFace, fontScale,color);
                imshow( "Display window", result );
            }

        }

        waitKey(0);
        return 0;
}



#include "processfilters.h"

#include <QDebug>

ProcessFilters::ProcessFilters(int width, int height)
{
    this->width  = width;
    this->height = height;

    gray = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );
    slit = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 3 );
}

ProcessFilters::~ProcessFilters()
{
    cvReleaseImage(&gray);
    cvReleaseImage(&slit);
}

void ProcessFilters::filterKuwahara(IplImage *image, IplImage *result, int kernel_size)
{
    /*

      info:

      http://habrahabr.ru/post/151112/
      http://www.compvision.ru/forum/index.php?showtopic=616


Вот так быстрее считать дисперсию. Ёщё можно погуглить по запросу "Integral Image":
double m1 = 0.0, m2 = 0.0;
numType x;
for (i = 0; i < N; i++) {
   x = randNum();
   m1 += x; 
   m2 += x*x;
}

m1 /= N;
m2 /= N;

printf("       Average: %f\n", m1);
printf("Std. deviation: %f\n", sqrt(m2-m1*m1));


Только, наверное, интенсивность для дисперсии нужно общую брать (max(r, g, b)). Иначе, представим, что в по красной компоненте наибольшая дисперсия в левом верхнем квадранте, по зелёной — в правом верхнем, по синей — где нибудь ещё. В итоге будут взяты средние значения компонент из разных квадрантов и получатся абсолютно новые цвета.


      */



    //int nchannels= image->nChannels;
    int w=image->width;
    int h=image->height;

    int dt=kernel_size/2;

    //TODO: расширить изображение-убрать черные края.

    cvCvtColor(image, gray, CV_RGB2GRAY);


    for( int y=2*dt; y <h-2*dt ; ++y )
    {
            uchar* ptr = (uchar*) (gray->imageData + y*gray->widthStep);
            uchar* p_out = (uchar*) (result->imageData + y*result->widthStep);
            for( int x=2*dt; x <w-2*dt; ++x )
            {
                     int gr=0;
                     int sum=0;
                     double mean1=0;
                     double mean2=0;
                     double mean3=0;
                     double mean4=0;
                     double disp1=0;
                     double disp2=0;
                     double disp3=0;
                     double disp4=0;

                     int k=0;
                     //1
                     sum=0;
                     mean1=0;
                     uchar* pd=ptr;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=-dt;k2<=0;++k2)
                            {
                                    sum+=pd[x+k2];

                                    ++k;
                            }
                            pd+= gray->widthStep;
                     }
                     mean1=sum/((dt+1)*(dt+1));

                     pd=ptr;
                     disp1=0;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=-dt;k2<=0;++k2)
                            {
                                    disp1+=(pd[x+k2]-mean1)*(pd[x+k2]-mean1);
                            }
                            pd+= gray->widthStep;
                     }

                     //2
                     sum=0;
                     mean2=0;
                     pd=ptr+dt*gray->widthStep;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=-dt;k2<=0;++k2)
                            {
                                    sum+=pd[x+k2];
                            }
                            pd+= gray->widthStep;
                     }
                     mean2=sum/((dt+1)*(dt+1));

                     pd=ptr+dt*gray->widthStep;
                     disp2=0;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=-dt;k2<=0;++k2)
                            {
                                    disp2+=(pd[x+k2]-mean2)*(pd[x+k2]-mean2);
                            }
                            pd+= gray->widthStep;
                     }

                     //3
                     sum=0;
                     mean3=0;
                     pd=ptr;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=0;k2<=dt;++k2)
                            {
                                    sum+=pd[x+k2];
                            }
                            pd+= gray->widthStep;
                     }
                     mean3=sum/((dt+1)*(dt+1));

                     pd=ptr;
                     disp3=0;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=0;k2<=dt;++k2)
                            {
                                    disp3+=(pd[x+k2]-mean3)*(pd[x+k2]-mean3);
                            }
                            pd+= gray->widthStep;
                     }

                     //4
                     sum=0;
                     mean4=0;
                     pd=ptr+dt*gray->widthStep;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=0;k2<=dt;++k2)
                            {
                                    sum+=pd[x+k2];
                            }
                            pd+= gray->widthStep;
                     }
                     mean4=sum/((dt+1)*(dt+1));

                     pd=ptr+dt*gray->widthStep;
                     disp4=0;
                     for (int k1=0;k1<=dt;++k1)
                     {
                            for(int k2=0;k2<=dt;++k2)
                            {
                                    disp4+=(pd[x+k2]-mean4)*(pd[x+k2]-mean4);
                            }
                            pd+= gray->widthStep;
                     }

                    gr=0;
                    if((disp1<=disp2)&&(disp1<=disp3)&&(disp1<=disp4))
                            gr=mean1;
                    if((disp2<=disp1)&&(disp2<=disp3)&&(disp2<=disp4))
                            gr=mean2;
                    if((disp3<=disp1)&&(disp3<=disp2)&&(disp3<=disp4))
                            gr=mean3;
                    if((disp4<=disp1)&&(disp4<=disp2)&&(disp4<=disp3))
                            gr=mean4;

                    p_out[x]= gr;
            }
    }

}

void ProcessFilters::slitImage(IplImage *image)
{
    // for 3 channels
    int c = image->nChannels;

    for( int y=0; y<image->height; y++ ) {

        // Получаем указатели на начало строки 'y'
        uchar* img_ptr = (uchar*) (image->imageData + y * image->widthStep);
        uchar* res_ptr = (uchar*) (slit->imageData + y * slit->widthStep);

        res_ptr[ c*image->width - c*21 + 0 ] = img_ptr[ c*image->width - c*20 + 0 ];
        res_ptr[ c*image->width - c*21 + 1 ] = img_ptr[ c*image->width - c*20 + 1 ];
        res_ptr[ c*image->width - c*21 + 2 ] = img_ptr[ c*image->width - c*20 + 2 ];


        for( int x=1; x<image->width-20; x++ ) {
            res_ptr[c*x - c + 0] = res_ptr[c*x + 0];
            res_ptr[c*x - c + 1] = res_ptr[c*x + 1];
            res_ptr[c*x - c + 2] = res_ptr[c*x + 2];
        }

    }
}


















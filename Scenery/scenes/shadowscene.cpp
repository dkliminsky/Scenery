#include "shadowscene.h"

ShadowScene::ShadowScene()
{
    control(shadow_width=200, "shadow_width", 0, 200);
    control(shadow_height=200, "shadow_height", 0, 200);
    control(shadow_shift=50, "shadow_shift", -200, 200);
    control(backColor=Color(1,1,1,0.2), "Background");
	control(shadowColor = Color(1, 1, 1, 1), "Shadow");

    control(depth_min=0, "depth_min", 0, 255);
    control(depth_max=255, "depth_max", 0, 255);
}

void ShadowScene::setup()
{
}

void ShadowScene::resize()
{
    background(1, 1, 1, 1);
}

void ShadowScene::paint()
{
    size(200, 200);
    background(backColor);

    Mat &depth = process(0)->mat;
    if (!depth.empty()) {
//        Mat color3 = color.clone();
//        cv::cvtColor(color, color3, COLOR_RGBA2RGB);
//		qDebug() << depth.depth() << depth.channels();			

		int i,j;
		int ch = depth.channels();
		int cols = depth.cols*ch;
        uchar* p;
        for( i = 0; i < depth.rows; ++i)
        {
            p = depth.ptr<uchar>(i);
            for ( j = 0; j < cols; j+=ch)
            {
                if (p[j + 0] > depth_min && p[j] < depth_max) {
                    p[j + 3] = 255;
                }
                else {
                    p[j + 3] = 0;
                }
            }
        }

		Mat depth_big;
		cv::resize(depth, depth_big, Size(640, 480));

		imageShadow.set(depth_big);
        imageShadow.bind();
		color(shadowColor);
        image(&imageShadow, 100 + shadow_shift, (200 - shadow_height) + (shadow_height / 2), shadow_width, shadow_height);
    }
}

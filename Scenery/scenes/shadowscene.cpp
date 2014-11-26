#include "shadowscene.h"

ShadowScene::ShadowScene()
{
    control(is_active=true, "is_active");
    control(shadow_width=200, "shadow_width", 0, 400);
    control(shadow_height=200, "shadow_height", 0, 400);
    control(shadow_shift=50, "shadow_shift", -200, 200);
    control(shadow_vertical=50, "shadow_vertical", -200, 200);
    control(backColor=Color(1,1,1,0.2f), "Background");
	control(shadowColor = Color(1, 1, 1, 1), "Shadow");

    control(depth_min=0, "depth_min", 0, 255);
    control(depth_max=255, "depth_max", 0, 255);
    control(is_reverse=false, "is_reverse");
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

    if (!is_active)
        return;

    Mat &depth = process(0)->mat;
    if (!depth.empty()) {
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
        Mat depth_blur;
        cv::resize(depth, depth_big, Size(640, 480), 0, 0, INTER_CUBIC);
        cv::blur(depth_big, depth_blur, cv::Size(3, 3));

        imageShadow.set(depth_blur);
        imageShadow.bind();
		color(shadowColor);
        if (!is_reverse) {
//            image(&imageShadow, 100 + shadow_shift, (200 - shadow_height) + (shadow_height / 2),
//                  shadow_width, shadow_height);
            image(&imageShadow, 100 + shadow_shift, 100 + shadow_vertical,
                  shadow_width, shadow_height);
        }
        else {
//            image(&imageShadow, 100 + shadow_shift, (200 - shadow_height) + (shadow_height / 2),
//                  shadow_width, shadow_height, 0, ReverseType::Horizontal);
            image(&imageShadow, 100 + shadow_shift, 100 + shadow_vertical,
                  shadow_width, shadow_height, 0, ReverseType::Horizontal);
        }
    }
}

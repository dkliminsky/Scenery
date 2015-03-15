#include "nodes/manager.h"
#include "nodes/nodes.h"


#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;


class ShadowScene : public Scene
{
public:
    QString name() { return "Shadow"; }

    Image imageShadow;
    int shadow_width;
    int shadow_height;
    int shadow_vertical;
    int shadow_shift;
    Color backColor;
    Color shadowColor;

    int depth_min;
    int depth_max;

    bool is_active;
    bool is_reverse;

    ShadowScene()
    {
        control(is_active=true, "is_active");
        control(shadow_width=200, "shadow_width", 0, 400);
        control(shadow_height=200, "shadow_height", 0, 400);
        control(shadow_shift=50, "shadow_shift", -200, 200);
        control(shadow_vertical=50, "shadow_vertical", -200, 200);
        //control(backColor=Color(1,1,1,0.2f), "Background");
        //control(shadowColor = Color(1, 1, 1, 1), "Shadow");

        control(depth_min=0, "depth_min", 0, 255);
        control(depth_max=255, "depth_max", 0, 255);
        control(is_reverse=false, "is_reverse");
    }

    virtual void setup() {}

    virtual void resize()
    {
        background(1, 1, 1, 1);
    }

    virtual void paint()
    {
        size(200, 200);
        background(1, 1, 0, 1);

        if (!is_active)
            return;

        Mat &depth = input(0)->mat;
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
            color(1, 1, 1, 1);
            if (!is_reverse) {
    //            image(&imageShadow, 100 + shadow_shift, (200 - shadow_height) + (shadow_height / 2),
    //                  shadow_width, shadow_height);
                draw(&imageShadow, 100 + shadow_shift, 100 + shadow_vertical,
                      shadow_width, shadow_height);
            }
            else {
    //            image(&imageShadow, 100 + shadow_shift, (200 - shadow_height) + (shadow_height / 2),
    //                  shadow_width, shadow_height, 0, ReverseType::Horizontal);
                draw(&imageShadow, 100 + shadow_shift, 100 + shadow_vertical,
                      shadow_width, shadow_height, 0, ReverseType::Horizontal);
            }
        }
    }
};


class KinectManager : public Manager
{
public:
    virtual void init()
    {
        Node *kinectNode = new KinectNode();
        kinectNode->setPos(0, 0);
        sources.append(kinectNode);
        nodes.append(kinectNode);

        Node *debugColorNode = new DebugNode();
        debugColorNode->setPos(200, 0);
        nodes.append(debugColorNode);

        Node *debugDepthNode = new DebugNode();
        debugDepthNode->setPos(200, 50);
        nodes.append(debugDepthNode);

//        kinectNode->outputs.at(0)->links.append(new Link(debugColorNode, 0));
//        kinectNode->outputs.at(1)->links.append(new Link(debugDepthNode, 0));

        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->setPos(200, 100);
        scenesNode->setScene(new ShadowScene);
        nodes.append(scenesNode);

        kinectNode->outputs.at(1)->links.append(new Link(scenesNode, 0));
    }
};

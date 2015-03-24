#include "nodes/manager.h"
#include "nodes/nodes.h"


#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;


class ShadowScene : public Scene
{
public:
    QString name() { return "Shadow"; }

    int depth_min;
    int depth_max;
    int blur_size;
    int dilation_size;

    Image imageShadow;
    Color backColor;
    Color shadowColor;

    bool is_active;
    bool is_reverse;

    ShadowScene()
    {
        control(depth_min=0, "depth_min", 0, 255);
        control(depth_max=255, "depth_max", 0, 255);
        control(blur_size=5, "Blur size", 1, 50);
        control(dilation_size=1, "Erosion size", 0, 50);

        control(is_active=true, "is_active");
        control(backColor=Color(1, 1, 1, 0.2f), "Background");
        control(shadowColor = Color(0, 0, 0, 1), "Shadow");

        control(is_reverse=false, "is_reverse");
    }

    virtual void paint()
    {
        Mat &depth = input(1)->mat;
        Rect pos = input(3)->rect;

        if (depth.empty())
            return;

        size(320, 240);
        background(backColor);

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
                    p[j + 0] = 255;
                    p[j + 1] = 255;
                    p[j + 2] = 255;
                    p[j + 3] = 255;
                }
                else {
                    p[j + 3] = 0;
                }
            }
        }

        Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                                Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                                Point( dilation_size, dilation_size ));
        Mat depth_dilate;
        Mat depth_big;
        Mat depth_blur;
        cv::dilate(depth, depth_dilate, element);
        cv::resize(depth_dilate, depth_big, Size(960, 720), 0, 0, INTER_CUBIC);
        cv::blur(depth_big, depth_blur, cv::Size(blur_size, blur_size));

        imageShadow.set(depth_blur);
        color(shadowColor);
//        if (!is_reverse) {
//            draw(&imageShadow, width()/2 + shadow_shift, height()/2 + shadow_vertical,
//                  shadow_width, shadow_height);
//        }
//        else {
//            draw(&imageShadow, width()/2 + shadow_shift, height()/2 + shadow_vertical,
//                  shadow_width, shadow_height, 0, ReverseType::Horizontal);
//        }

        draw(&imageShadow, pos.x, pos.y, pos.width, pos.height);


    }

    void self_shadow(Rect pos)
    {
        draw(&imageShadow, pos.x, pos.y, pos.width, pos.height);
    }
};


class TailHandsScene : public Scene
{
public:
    QString name() { return "Tail Hands"; }

    Color backColor;
    Color tailColor;
    Image *tailImage;
    int tailSize;

    Image *stream;

    TailHandsScene()
    {
        stream = new Image();
        control(backColor=Color(0, 0, 0, 0.2f), "Back color");
        control(tailColor=Color(1, 0, 0, 1), "Tail color");
        control(tailSize=20, "Tail Size", 0, 50);
        control(&tailImage, "Tail hands", "images/forms/", "circle01.png");

    }

    virtual void paint()
    {
        Mat kinectColor = input(0)->mat;
        vector<Human> &humans = input(2)->humans;

        size(320, 240);
        background(backColor);


        color(tailColor);
        for (int i=0; i < humans.size(); ++i) {
            Human &human = humans.at(i);
            if (human.isTracking) {
                draw(tailImage, human.wristRight.x, human.wristRight.y, tailSize, tailSize);
                draw(tailImage, human.wristLeft.x, human.wristLeft.y, tailSize, tailSize);
            }
        }

    }
};


class Manager_ : public Manager
{
public:
    void init()
    {
        Node *kinectNode = new KinectNode();
        kinectNode->setPos(0, 0);
        sources.append(kinectNode);
        nodes.append(kinectNode);

        Node *positionNode = new CameraPositionNode();
        positionNode->setPos(0, 200);
        nodes.append(positionNode);
        sources.append(positionNode);

        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->inputs.append(new Port(PortType::Humans));
        scenesNode->inputs.append(new Port(PortType::Rect));
        scenesNode->setPos(200, 100);
        scenesNode->addScene(new ShadowScene);
        scenesNode->addScene(new TailHandsScene);
        nodes.append(scenesNode);

        kinectNode->outputs.at(0)->links.append(new Link(scenesNode, 0));
        kinectNode->outputs.at(1)->links.append(new Link(scenesNode, 1));
        kinectNode->outputs.at(2)->links.append(new Link(scenesNode, 2));
        positionNode->outputs.at(0)->links.append(new Link(scenesNode, 3));
    }
};

#include "nodes/manager.h"
#include "nodes/nodes.h"


#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;

enum class Signals { None, DoubleLeft, DoubleRight, DoubleReturn, StrikeLeft, StrikeRight };
enum class DoubleShadowCommand {None, Left, Right, Return};

class ShadowScene : public Scene
{
public:
    QString name() { return "Shadow"; }
    Rect pos;

    int depth_min;
    int depth_max;
    int blur_size;
    int dilation_size;

    Image imageShadow;
    Color backColor;

    bool is_self_shadow;
    Color self_shadow_color;

    bool is_double_shadow;
    Color double_shadow_color;
    int double_shadow_max_shift;
    int double_shadow_shift_time;
    bool is_reverse;
    int double_shadow_shift;
    Signals double_shadow_command;

    bool is_strike_shadow;
    Color strike_shadow_color;

    ShadowScene()
    {
        control(depth_min=50, "depth_min", 0, 255);
        control(depth_max=110, "depth_max", 0, 255);
        control(blur_size=7, "Blur size", 1, 50);
        control(dilation_size=1, "Erosion size", 0, 50);
        control(backColor=Color(1, 1, 1, 0.2f), "Background");

        control(is_self_shadow=true, "Self Shadow");
        control(self_shadow_color = Color(0, 0, 0, 1), "Self Shadow Color");

        control(is_double_shadow=false, "Double Shadow");
        button(int(Signals::DoubleLeft), "Double Left");
        button(int(Signals::DoubleRight), "Double Right");
        button(int(Signals::DoubleReturn), "Double Return");
        control(double_shadow_color = Color(0, 0, 0, 1), "Double Shadow Color");
        control(double_shadow_max_shift=60, "Double Shadow Shift", 0, 100);
        control(double_shadow_shift_time=300, "Double Shadow Shift Time", 0, 500);
        control(is_reverse=false, "is_reverse");
        double_shadow_command = Signals::None;
        double_shadow_shift = 0;

        control(is_strike_shadow=true, "Self Shadow");
        button(int(Signals::StrikeLeft), "Strike Left");
        button(int(Signals::StrikeRight), "Strike Right");
        control(strike_shadow_color = Color(0.8f, 0, 0, 1), "Self Shadow Color");
    }

    void selfShadow() {
        color(self_shadow_color);
        draw(&imageShadow, pos.x, pos.y, pos.width, pos.height);
    }

    void doubleShadow() {
        if (is_reverse) {
            imageShadow.setReverse(ReverseType::Horizontal);
        }

        int step = float(dtime())/float(double_shadow_shift_time)*double_shadow_max_shift;
        if (double_shadow_command == Signals::DoubleLeft) {
            double_shadow_shift -= step;
            if (double_shadow_shift < -double_shadow_max_shift) {
                double_shadow_shift = -double_shadow_max_shift;
                double_shadow_command = Signals::None;
            }
        }
        if (double_shadow_command == Signals::DoubleRight) {
            double_shadow_shift += step;
            if (double_shadow_shift > double_shadow_max_shift) {
                double_shadow_shift = double_shadow_max_shift;
                double_shadow_command = Signals::None;
            }
        }
        if (double_shadow_command == Signals::DoubleReturn) {
            if (-step <= double_shadow_shift && double_shadow_shift <= step) {
                double_shadow_shift = 0;
                double_shadow_command = Signals::None;
            }
            else {
                if (double_shadow_shift > 0) {
                    double_shadow_shift -= step;
                }
                else {
                    double_shadow_shift += step;
                }
            }
        }

        color(double_shadow_color);
        draw(&imageShadow, pos.x + double_shadow_shift, pos.y, pos.width, pos.height);
        imageShadow.setReverse(ReverseType::None);
    }

    void strikeShadow() {
        color(strike_shadow_color);
        draw(&imageShadow, pos.x, pos.y, pos.width, pos.height);
    }

    virtual void paint()
    {
        Mat &depth = input(1)->mat;
        pos = input(3)->rect;

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

        if (is_self_shadow)
            selfShadow();
        if (is_double_shadow)
            doubleShadow();
        if (is_double_shadow)
            doubleShadow();
    }

    virtual void signal(int id)
    {
        Particle *particle;

        switch (id) {
        case Signals::DoubleLeft:
            double_shadow_command = Signals::DoubleLeft;
            break;
        case Signals::DoubleRight:
            double_shadow_command = Signals::DoubleRight;
            break;
        case Signals::DoubleReturn:
            double_shadow_command = Signals::DoubleReturn;
            break;
        case Signals::StrikeLeft:
            particle = new Particle(&imageShadow, false);
            particle->setPos(pos);
            particle->setTTL(300);
            addParticle(particle);
            break;
        case Signals::StrikeRight:
            particle = new Particle(&imageShadow, false);
            particle->setPos(pos);
            particle->setTTL(300);
            addParticle(particle);
            break;
        default:
            break;
        }
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

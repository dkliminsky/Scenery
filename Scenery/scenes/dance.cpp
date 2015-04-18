#include "nodes/project.h"
#include "nodes/nodes.h"


#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;

enum class Signals { None, DoubleLeft, DoubleRight, DoubleReturn, StrikeLeft, StrikeRight,
                     Dead };

class ShadowScene : public Scene
{
public:
    QString name() { return "Shadow"; }
    Rect pos;
    Image stream;

    int depth_min;
    int depth_max;
    int blur_size;
    int erosion_size;
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
    double strike_shadow_disappear;
    double strike_shadow_acceleartion;
    Signals strike_shadow_command;

    bool is_dead_shadow;
    Color dead_shadow_color;
    double dead_shadow_disappear;
    double dead_shadow_acceleartion;
    int dead_shadow_erode;
    Signals dead_shadow_command;

    ShadowScene()
    {
        addControlGroup("Main");
        control(depth_min=50, "Depth min", 0, 255);
        control(depth_max=110, "Depth max", 0, 255);
        control(blur_size=7, "Blur size", 1, 50);
        control(erosion_size=1, "Erosion size", 0, 50);
        control(dilation_size=1, "Dilation size", 0, 50);
        control(backColor=Color(1, 1, 1, 0.2f), "Background");

        addControlGroup("Self Shadow");
        control(is_self_shadow=true, "On");
        control(self_shadow_color = Color(0, 0, 0, 1), "Color");

        addControlGroup("Double Shadow");
        control(is_double_shadow=false, "On");
        button(int(Signals::DoubleLeft), "Left");
        button(int(Signals::DoubleRight), "Right");
        button(int(Signals::DoubleReturn), "Return");
        control(double_shadow_color = Color(0, 0, 0, 1), "Color");
        control(double_shadow_max_shift=60, "Shift", 0, 100);
        control(double_shadow_shift_time=300, "Shift Time", 0, 500);
        control(is_reverse=false, "Reverse");
        double_shadow_command = Signals::None;
        double_shadow_shift = 0;

        addControlGroup("Strike Shadow");
        control(is_strike_shadow=true, "On");
        button(int(Signals::StrikeLeft), "Left");
        button(int(Signals::StrikeRight), "Right");
        control(strike_shadow_color = Color(0.8f, 0, 0, 1), "Color");
        control(strike_shadow_disappear=0.001, "Disappear", 0, 1, 4);
        control(strike_shadow_acceleartion=0.4, "Acceleration", 0, 10, 2);
        strike_shadow_command = Signals::None;

        addControlGroup("Dead Shadow");
        control(is_dead_shadow=true, "On");
        button(int(Signals::Dead), "Dead");
        control(dead_shadow_color = Color(0, 0.2f, 0, 1), "Color");
        control(dead_shadow_disappear=0.001, "Disappear", 0, 1, 4);
        control(dead_shadow_acceleartion=0.2, "Acceleration", 0, 10, 2);
        control(dead_shadow_erode=1, "Erosion", 0, 50);
        dead_shadow_command = Signals::None;
    }

    void selfShadow() {
        color(self_shadow_color);
        draw(&imageShadow, pos.x, pos.y, pos.width, pos.height);
    }

    void doubleShadow() {
        if (is_reverse && double_shadow_command != Signals::None) {
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
        if (strike_shadow_command == Signals::None)
            return;

        Particle *particle;
        particle = new Particle(&imageShadow, false);
        particle->setPos(pos);
        particle->setColor(strike_shadow_color);
        particle->setTTL(2000);
        particle->setDisappear(strike_shadow_disappear);
        if (strike_shadow_command == Signals::StrikeLeft) {
            particle->setAcceleration(-strike_shadow_acceleartion, 0);
        }
        else {
            particle->setAcceleration(strike_shadow_acceleartion, 0);
        }
        addParticle(particle);
        strike_shadow_command = Signals::None;
    }

    void deadShadow() {
        if (dead_shadow_command == Signals::None)
            return;

        Mat erode_element =
                cv::getStructuringElement(cv::MORPH_RECT,
                                          Size( 2*dead_shadow_erode + 1,
                                                2*dead_shadow_erode+1 ),
                                          Point( dead_shadow_erode, dead_shadow_erode ));
        Mat depth_erode;
        cv::erode(imageShadow.mat(), depth_erode, erode_element);

        Particle *particle;
        particle = new Particle(depth_erode);
        particle->setPos(pos);
        particle->setColor(dead_shadow_color);
        particle->setTTL(2000);
        particle->setDisappear(dead_shadow_disappear);
        particle->setAcceleration(0, -dead_shadow_acceleartion);
        addParticle(particle);
        dead_shadow_command = Signals::None;
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

        Mat erode_element =
                cv::getStructuringElement(cv::MORPH_RECT,
                                          Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                          Point( erosion_size, erosion_size ));
        Mat dilate_element =
                cv::getStructuringElement(cv::MORPH_RECT,
                                          Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                          Point( dilation_size, dilation_size ));

        Mat depth_erode;
        Mat depth_dilate;
        Mat depth_big;
        Mat depth_blur;
        cv::erode(depth, depth_erode, erode_element);
        cv::dilate(depth_erode, depth_dilate, dilate_element);
        cv::resize(depth_dilate, depth_big, Size(960, 720), 0, 0, INTER_CUBIC);
        cv::blur(depth_big, depth_blur, cv::Size(blur_size, blur_size));

        imageShadow.set(depth_blur);

        if (is_self_shadow)
            selfShadow();
        if (is_double_shadow) {
            gestures();
            doubleShadow();
        }
        if (is_strike_shadow)
            strikeShadow();
        if (is_dead_shadow)
            deadShadow();
    }

    virtual void signal(int id)
    {
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
            strike_shadow_command = Signals::StrikeLeft;
            break;
        case Signals::StrikeRight:
            strike_shadow_command = Signals::StrikeRight;
            break;
        case Signals::Dead:
            dead_shadow_command = Signals::Dead;
            break;
        default:
            break;
        }
    }

    void gestures()
    {
        vector<bool> &gests = input(4)->booleans;
        if (gests.at(0)) {
            double_shadow_command = Signals::DoubleRight;
        }
        if (gests.at(1)) {
            double_shadow_command = Signals::DoubleLeft;
        }
    }

};


class RaysScene : public Scene
{
public:
    QString name() { return "Rays"; }

    Image stream;
    Color backColor;
    Color rayColor;
    Image *rayImage;
    int raySize;
    int haloSize;
    bool isDemo;

    RaysScene()
    {
        control(backColor=Color(1, 1, 1, 0.8f), "Back color");
        control(isDemo=true, "Demo");
        control(&rayImage, "Image", "images/rays/", "ray_04.png");
        control(rayColor=Color(1, 0, 0, 1), "Ray color");
        control(raySize=200, "Ray Size", 0, 1000);
        control(haloSize=100, "Halo Size", 0, 1000);
    }

    void drawRay(Point from, Point to)
    {
        float a = angle(from.x, from.y, to.x, to.y);

        if (a > pi()/4 && a < pi() - pi()/4)
            return;

        if (a > pi() + pi()/4 && a < 2*pi() - pi()/4)
            return;

        float s = raySize;
        float x = from.x;
        float y = from.y;

        x += s/2 * cos(a);
        y -= s/2 * sin(a);

        draw(rayImage, x, y, s, s, a);
    }

    void drawRayFromCenter(Point center, Point to)
    {
        float a = angle(center.x, center.y, to.x, to.y);
        float d = distance(float(center.x), center.y, to.x, to.y);

        if (d < haloSize)
            return;

        if (a > pi()/4 && a < pi() - pi()/4)
            return;

        if (a > pi() + pi()/4 && a < 2*pi() - pi()/4)
            return;

        float s = raySize;
        float x = center.x;
        float y = center.y;

        x += s/2 * cos(a);
        y -= s/2 * sin(a);

        draw(rayImage, x, y, s, s, a);
    }

    virtual void paint()
    {
        Mat &kinectColor = input(0)->mat;
        Human &human = input(2)->human;
        //Mat &kinectDepth = input(1)->mat;
        Rect pos = input(3)->rect;

        if (kinectColor.empty())
            return;

        size(320*2, 240*2);
        background(backColor);

        //draw(&stream, pos.x, pos.y, pos.width, pos.height);
        color(1,1,1);

        if (isDemo) {
            Mat kinectColor3;
            cv::cvtColor(kinectColor, kinectColor3, COLOR_RGBA2RGB);
            stream.set(kinectColor3);
            draw(&stream, width()/2, height()/2, width(), height());
        }
        else {

        }

        flush();

        color(rayColor);
        if (human.isTracking) {
            drawRay(human.shoulderCenter, human.head);

            Point center;
            center.x = (human.shoulderCenter.x + human.spine.x)/2;
            center.y = (human.shoulderCenter.y + human.spine.y)/2;

            drawRayFromCenter(center, human.elbowLeft);
            drawRayFromCenter(center, human.elbowRight);
            drawRayFromCenter(center, human.handLeft);
            drawRayFromCenter(center, human.handRight);
            drawRayFromCenter(center, human.kneeLeft);
            drawRayFromCenter(center, human.kneeRight);
            drawRayFromCenter(center, human.ankleLeft);
            drawRayFromCenter(center, human.ankleRight);
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
        Mat &depth = input(1)->mat;
        Human &human = input(2)->human;
        Rect pos = input(3)->rect;

        if (depth.empty())
            return;

        size(320*2, 240*2);
        background(backColor);

        color(tailColor);
        if (human.isTracking) {
            draw(tailImage, human.wristRight.x, human.wristRight.y, tailSize, tailSize);
            draw(tailImage, human.wristLeft.x, human.wristLeft.y, tailSize, tailSize);
        }
    }
};


class Manager_ : public Project
{
public:
    void init()
    {
        Node *kinectNode = new KinectNode();
        kinectNode->setPos(0, 0);
        nodes.append(kinectNode);

        Node *rectNode = new RectNode();
        rectNode->setPos(0, 200);
        nodes.append(rectNode);

        Node *gestureNode = new GestureNode();
        gestureNode->setPos(0, 400);
        nodes.append(gestureNode);

        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->inputs.append(new Port(PortType::Human));
        scenesNode->inputs.append(new Port(PortType::Rect));
        scenesNode->inputs.append(new Port(PortType::Booleans));
        scenesNode->setPos(200, 100);
        scenesNode->addScene(new RaysScene);
        scenesNode->addScene(new ShadowScene);
        scenesNode->addScene(new TailHandsScene);
        nodes.append(scenesNode);

        kinectNode->outputs.at(2)->links.append(new Link(gestureNode, 0));
        kinectNode->outputs.at(0)->links.append(new Link(scenesNode, 0));
        kinectNode->outputs.at(1)->links.append(new Link(scenesNode, 1));
        kinectNode->outputs.at(2)->links.append(new Link(scenesNode, 2));
        rectNode->outputs.at(0)->links.append(new Link(scenesNode, 3));
        gestureNode->outputs.at(0)->links.append(new Link(scenesNode, 4));
    }
};

#include "nodes/project.h"
#include "nodes/nodes.h"

#include "scenes/shadow.cpp"


//enum class Signals { None, DoubleLeft, DoubleRight, DoubleReturn, StrikeLeft, StrikeRight,
//                     Dead };

//class ShadowScene : public Scene
//{
//public:
//    QString name() { return "Shadow"; }
//    Rect pos;
//    Image imageShadow;
//    Color backColor;

//    QString shadow_type;
//    int blur_size;
//    int erosion_size;
//    int dilation_size;

//    bool is_self_shadow;
//    Color self_shadow_color;

//    bool is_move_shadow;
//    Color move_shadow_color;
//    int inclination_deg;
//    int move_speed;
//    int move_max_x;
//    double move_x_stop;
//    float move_shadow_x;

//    bool is_double_shadow;
//    Color double_shadow_color;
//    int double_shadow_max_shift;
//    int double_shadow_shift_time;
//    bool is_reverse;
//    int double_shadow_shift;
//    Signals double_shadow_command;

//    bool is_strike_shadow;
//    Color strike_shadow_color;
//    double strike_shadow_disappear;
//    double strike_shadow_acceleartion;
//    Signals strike_shadow_command;

//    bool is_dead_shadow;
//    Color dead_shadow_color;
//    double dead_shadow_disappear;
//    double dead_shadow_acceleartion;
//    int dead_shadow_erode;
//    Signals dead_shadow_command;

//    ShadowScene()
//    {
//        addControlGroup("Main");
//        addControl(backColor=Color(1, 1, 1, 0.2f), "Background");

//        addControlGroup("Shadow");
//        addControl(shadow_type="natural", "Shadow type", QStringList() << "smoke" << "8bit");
//        addControl(blur_size=7, "Blur size", 0, 50);
//        addControl(erosion_size=1, "Erosion size", 0, 50);
//        addControl(dilation_size=1, "Dilation size", 0, 50);

//        addControlGroup("Self Shadow");
//        addControl(is_self_shadow=true, "On Self");
//        addControl(self_shadow_color = Color(0, 0, 0, 1), "Color Self");

//        addControlGroup("Move Shadow");
//        addControl(is_move_shadow=true, "Move Self");
//        addControl(move_shadow_color = Color(0, 0, 0, 1), "Color Self");
//        addControl(inclination_deg=30, "Min Inclination", 0, 90);
//        addControl(move_speed=10, "Move speed", 0, 1000);
//        addControl(move_max_x=100, "Move x max", 0, 1000);
//        addControl(move_x_stop=0.15, "Move x stop", 0, 1000, 3);
//        move_shadow_x = 0;

//        addControlGroup("Double Shadow");
//        addControl(is_double_shadow=false, "On Double");
//        addButton(int(Signals::DoubleLeft), "Left Double");
//        addButton(int(Signals::DoubleRight), "Right Double");
//        addButton(int(Signals::DoubleReturn), "Return Double");
//        addControl(double_shadow_color = Color(0, 0, 0, 1), "Color Double");
//        addControl(double_shadow_max_shift=60, "Shift Double", 0, 300);
//        addControl(double_shadow_shift_time=300, "Shift Time Double", 0, 500);
//        addControl(is_reverse=false, "Reverse Double");
//        double_shadow_command = Signals::None;
//        double_shadow_shift = 0;

//        addControlGroup("Strike Shadow");
//        addControl(is_strike_shadow=true, "On Strike");
//        addButton(int(Signals::StrikeLeft), "Left Strike");
//        addButton(int(Signals::StrikeRight), "Right Strike");
//        addControl(strike_shadow_color = Color(0.8f, 0, 0, 1), "Color Strike");
//        addControl(strike_shadow_disappear=0.001, "Disappear Strike", 0, 1, 4);
//        addControl(strike_shadow_acceleartion=0.4, "Acceleration Strike", 0, 10, 2);
//        strike_shadow_command = Signals::None;

//        addControlGroup("Dead Shadow");
//        addControl(is_dead_shadow=true, "On Dead");
//        addButton(int(Signals::Dead), "Dead Action");
//        addControl(dead_shadow_color = Color(0, 0.2f, 0, 1), "Color Dead");
//        addControl(dead_shadow_disappear=0.001, "Disappear Dead", 0, 1, 4);
//        addControl(dead_shadow_acceleartion=0.2, "Acceleration Dead", 0, 10, 2);
//        addControl(dead_shadow_erode=1, "Erosion Dead", 0, 50);
//        dead_shadow_command = Signals::None;
//    }

//    virtual void paint()
//    {
//        Mat &hit = input("hit")->mat;
//        pos = input("rect")->rect;

//        if (hit.empty())
//            return;

//        prepareShadow();

//        size(320, 240);
//        background(backColor);

//        if (is_self_shadow)
//            selfShadow();
//        if (is_move_shadow)
//            moveShadow();
//        if (is_double_shadow) {
//            doubleShadow();
//        }
//        if (is_strike_shadow)
//            strikeShadow();
//        if (is_dead_shadow)
//            deadShadow();
//    }

//    void prepareShadow() {
//        Mat &hit = input("hit")->mat;
//        Mat erode_element =
//                cv::getStructuringElement(cv::MORPH_RECT,
//                                          Size( 2*erosion_size + 1, 2*erosion_size+1 ),
//                                          Point( erosion_size, erosion_size ));
//        Mat dilate_element =
//                cv::getStructuringElement(cv::MORPH_RECT,
//                                          Size( 2*dilation_size + 1, 2*dilation_size+1 ),
//                                          Point( dilation_size, dilation_size ));

//        Mat depth_erode;
//        Mat depth_dilate;
//        Mat depth_big;
//        cv::erode(hit, depth_erode, erode_element);
//        cv::dilate(depth_erode, depth_dilate, dilate_element);
//        cv::resize(depth_dilate, depth_big, Size(960, 720), 0, 0, INTER_CUBIC);
//        if (blur_size > 0) {
//            Mat depth_blur;
//            cv::blur(depth_big, depth_blur, cv::Size(blur_size, blur_size));
//            imageShadow.set(depth_blur);
//        }
//        else {
//            imageShadow.set(depth_big);
//        }
//    }

//    void drawShadow(float x, float y) {
//        draw(&imageShadow, pos.x + x, pos.y + y, pos.width, pos.height);
//    }

//    void selfShadow() {
//        color(self_shadow_color);
//        draw(&imageShadow, pos.x, pos.y, pos.width, pos.height);
//    }

//    void moveShadow() {
//        color(move_shadow_color);
//        Human &human = input("human1")->human;

//        float a = angle(human.spine.x, human.spine.y,
//                        human.shoulderCenter.x, human.shoulderCenter.y);
//        float a_min = inclination_deg * pi() / 180;
//        float da = a - a_min;

//        //qDebug() << a << a_min << pi()/2 - a_min;

//        float dx = 0;

//        if (a < pi()/2 - a_min) {
//            dx = da * move_speed * move_shadow_x * move_x_stop + 2;
//        }
//        else if (a > pi()/2 + a_min) {
//            dx = - da * move_speed * move_shadow_x * move_x_stop - 2;
//        }

//        if (move_shadow_x > move_max_x)
//            move_shadow_x = move_max_x;

//        if (move_shadow_x < -move_max_x)
//            move_shadow_x = -move_max_x;


//        //move_shadow_x += dx * move_shadow_x * move_x_stop;
//        move_shadow_x += dx;
//        drawShadow(move_shadow_x, 0);
//    }

//    void doubleShadow() {
//        int step = float(dtime())/float(double_shadow_shift_time)
//                   * double_shadow_max_shift;
//        if (double_shadow_command == Signals::DoubleLeft) {
//            double_shadow_shift -= step;
//            if (double_shadow_shift < -double_shadow_max_shift) {
//                double_shadow_shift = -double_shadow_max_shift;
//                double_shadow_command = Signals::None;
//            }
//        }
//        if (double_shadow_command == Signals::DoubleRight) {
//            double_shadow_shift += step;
//            if (double_shadow_shift > double_shadow_max_shift) {
//                double_shadow_shift = double_shadow_max_shift;
//                double_shadow_command = Signals::None;
//            }
//        }
//        if (double_shadow_command == Signals::DoubleReturn) {
//            if (-step <= double_shadow_shift && double_shadow_shift <= step) {
//                double_shadow_shift = 0;
//                double_shadow_command = Signals::None;
//            }
//            else {
//                if (double_shadow_shift > 0) {
//                    double_shadow_shift -= step;
//                }
//                else {
//                    double_shadow_shift += step;
//                }
//            }
//        }

//        color(double_shadow_color);
//        draw(&imageShadow, pos.x + double_shadow_shift, pos.y, pos.width, pos.height);
//    }

//    void strikeShadow() {
//        if (strike_shadow_command == Signals::None)
//            return;

//        Particle *particle;
//        particle = new Particle(&imageShadow, false);
//        particle->setPos(pos);
//        particle->setColor(strike_shadow_color);
//        particle->setTTL(2000);
//        particle->setDisappear(strike_shadow_disappear);
//        if (strike_shadow_command == Signals::StrikeLeft) {
//            particle->setAcceleration(-strike_shadow_acceleartion, 0);
//        }
//        else {
//            particle->setAcceleration(strike_shadow_acceleartion, 0);
//        }
//        addParticle(particle);
//        strike_shadow_command = Signals::None;
//    }

//    void deadShadow() {
//        if (dead_shadow_command == Signals::None)
//            return;

//        Mat erode_element =
//                cv::getStructuringElement(cv::MORPH_RECT,
//                                          Size( 2*dead_shadow_erode + 1,
//                                                2*dead_shadow_erode+1 ),
//                                          Point( dead_shadow_erode, dead_shadow_erode ));
//        Mat depth_erode;
//        cv::erode(imageShadow.mat(), depth_erode, erode_element);

//        Particle *particle;
//        particle = new Particle(depth_erode);
//        particle->setPos(pos);
//        particle->setColor(dead_shadow_color);
//        particle->setTTL(2000);
//        particle->setDisappear(dead_shadow_disappear);
//        particle->setAcceleration(0, -dead_shadow_acceleartion);
//        addParticle(particle);
//        dead_shadow_command = Signals::None;
//    }

//    virtual void signal(int id)
//    {
//        qDebug() << "Set command:" << id;
//        switch (id) {
//        case Signals::DoubleLeft:
//            double_shadow_command = Signals::DoubleLeft;
//            break;
//        case Signals::DoubleRight:
//            double_shadow_command = Signals::DoubleRight;
//            break;
//        case Signals::DoubleReturn:
//            double_shadow_command = Signals::DoubleReturn;
//            break;
//        case Signals::StrikeLeft:
//            strike_shadow_command = Signals::StrikeLeft;
//            break;
//        case Signals::StrikeRight:
//            strike_shadow_command = Signals::StrikeRight;
//            break;
//        case Signals::Dead:
//            dead_shadow_command = Signals::Dead;
//            break;
//        default:
//            break;
//        }
//    }
//};


//class RaysScene : public Scene
//{
//public:
//    QString name() { return "Rays"; }

//    Rect pos;
//    Image imageHalo;
//    Image stream;
//    Color backColor;
//    Color rayColor;
//    Image *rayImage;
//    Image *ringTestImage;
//    int raySize;
//    int circleSize;
//    bool isDemo;
//    bool isTest;

//    int depth_min;
//    int depth_max;
//    int blur_size;
//    int erosion_size;
//    int dilation_size;
//    Color halo_color;

//    RaysScene()
//    {
//        addControl(backColor=Color(1, 1, 1, 0.8f), "Back color");
//        addControl(isDemo=true, "Demo");
//        addControl(isTest=true, "Test");
//        addControl(&rayImage, "Image", "images/rays/", "ray_04.png");
//        addControl(rayColor=Color(1, 0, 0, 1), "Ray color");
//        addControl(raySize=300, "Ray Size", 0, 1000);
//        addControl(circleSize=100, "Circle Size", 0, 1000);

//        addControl(depth_min=50, "Depth min", 0, 255);
//        addControl(depth_max=110, "Depth max", 0, 255);
//        addControl(blur_size=7, "Blur size", 1, 50);
//        addControl(erosion_size=1, "Erosion size", 0, 50);
//        addControl(dilation_size=1, "Dilation size", 0, 50);

//        addControl(halo_color = Color(0, 0, 0, 1), "Halo Self");

//        ringTestImage = new Image("images/forms/ring_01.png");
//    }

//    void drawRay(Point from, Point to)
//    {
//        float a = angle(from.x, from.y, to.x, to.y);

//        if (a > pi()/4.0 && a < pi() - pi()/4.0)
//            return;

//        if (a > pi() + pi()/4.0 && a < 2.0*pi() - pi()/4.0)
//            return;

//        float s = raySize;
//        float x = from.x;
//        float y = from.y;

//        x += s/2.0 * cos(a);
//        y -= s/2.0 * sin(a);

//        draw(rayImage,
//             float(x/2)*(float(pos.width)/320.0) + pos.x - pos.width/2,
//             float(y/2)*(float(pos.height)/240.0) + pos.y - pos.height/2,
//             float(s/2)*(float(pos.width)/320.0),
//             float(s/2)*(float(pos.height)/240.0),
//             a);
//    }

//    void drawRayFromCenter(Point center, Point to)
//    {
//        float a = angle(center.x, center.y, to.x, to.y);
//        float d = distance(float(center.x), center.y, to.x, to.y);

//        if (d < circleSize)
//            return;

////        if (a > pi()/4 && a < pi() - pi()/4)
////            return;

////        if (a > pi() + pi()/4 && a < 2*pi() - pi()/4)
////            return;

//        float s = raySize;
//        float x = center.x;
//        float y = center.y;

//        x += s/2.0 * cos(a);
//        y -= s/2.0 * sin(a);

//        draw(rayImage,
//             float(x/2)*(float(pos.width)/320.0) + pos.x - pos.width/2,
//             float(y/2)*(float(pos.height)/240.0) + pos.y - pos.height/2,
//             float(s/2)*(float(pos.width)/320.0),
//             float(s/2)*(float(pos.height)/240.0),
//             a);
//    }

//    virtual void paint()
//    {
//        Mat &kinectColor = input("color")->mat;
//        Human &human = input("human1")->human;
//        Mat &kinectDepth = input("depth")->mat;
//        pos = input("rect")->rect;

//        if (kinectColor.empty())
//            return;

//        size(320, 240);
//        background(backColor);
//        color(1,1,1);

//        if (isDemo) {
//            Mat kinectColor3;
//            cv::cvtColor(kinectColor, kinectColor3, COLOR_RGBA2RGB);
//            stream.set(kinectColor3);
//            draw(&stream, width()/2, height()/2, width(), height());
//        }
//        else {
//            int i,j;
//            int ch = kinectDepth.channels();
//            int cols = kinectDepth.cols*ch;
//            uchar* p;
//            for( i = 0; i < kinectDepth.rows; ++i)
//            {
//                p = kinectDepth.ptr<uchar>(i);
//                for ( j = 0; j < cols; j+=ch)
//                {
//                    if (p[j + 0] > depth_min && p[j] < depth_max) {
//                        p[j + 0] = 255;
//                        p[j + 1] = 255;
//                        p[j + 2] = 255;
//                        p[j + 3] = 255;
//                    }
//                    else {
//                        p[j + 3] = 0;
//                    }
//                }
//            }

//            Mat erode_element =
//                    cv::getStructuringElement(cv::MORPH_RECT,
//                                              Size( 2*erosion_size + 1, 2*erosion_size+1 ),
//                                              Point( erosion_size, erosion_size ));
//            Mat dilate_element =
//                    cv::getStructuringElement(cv::MORPH_RECT,
//                                              Size( 2*dilation_size + 1, 2*dilation_size+1 ),
//                                              Point( dilation_size, dilation_size ));

//            Mat depth_erode;
//            Mat depth_dilate;
//            Mat depth_big;
//            Mat depth_blur;
//            cv::erode(kinectDepth, depth_erode, erode_element);
//            cv::dilate(depth_erode, depth_dilate, dilate_element);
//            cv::resize(depth_dilate, depth_big, Size(960, 720), 0, 0, INTER_CUBIC);
//            cv::blur(depth_big, depth_blur, cv::Size(blur_size, blur_size));

//            color(halo_color);
//            imageHalo.set(depth_blur);

//            draw(&imageHalo, pos.x, pos.y, pos.width, pos.height);
//        }
//        flush();

//        color(rayColor);
//        if (human.isTracking) {
//            drawRay(human.shoulderCenter, human.head);

//            Point center;
//            center.x = (human.shoulderCenter.x + human.spine.x)/2;
//            center.y = (human.shoulderCenter.y + human.spine.y)/2;

//            if (isTest) {
//                //qDebug() << pos.x + float(center.x/2)*(float(pos.width)/320.0) << float(center.x) <<  pos.y + float(center.y/2)*(float(pos.height)/240.0) << float(center.y);
//                draw(ringTestImage,
//                     pos.x + float(center.x/2)*(float(pos.width)/320.0) - pos.width/2,
//                     pos.y + float(center.y/2)*(float(pos.height)/240.0) - pos.height/2,
//                     circleSize, circleSize);
//            }

//            drawRayFromCenter(center, human.elbowLeft);
//            drawRayFromCenter(center, human.elbowRight);
//            drawRayFromCenter(center, human.handLeft);
//            drawRayFromCenter(center, human.handRight);

//            drawRay(center, human.kneeLeft);
//            drawRay(center, human.kneeRight);
//            drawRay(center, human.ankleLeft);
//            drawRay(center, human.ankleRight);
//        }
//    }
//};


//class TailHandsScene : public Scene
//{
//public:
//    QString name() { return "Tail Hands"; }

//    Color backColor;
//    Color tailColor;
//    Image *tailImage;
//    int tailSize;

//    Image *stream;

//    TailHandsScene()
//    {
//        stream = new Image();
//        addControl(backColor=Color(0, 0, 0, 0.2f), "Back color");
//        addControl(tailColor=Color(1, 0, 0, 1), "Tail color");
//        addControl(tailSize=20, "Tail Size", 0, 50);
//        addControl(&tailImage, "Tail hands", "images/forms/", "circle01.png");

//    }

//    virtual void paint()
//    {
//        Mat &depth = input("depth")->mat;
//        Human &human = input("human1")->human;
//        Rect pos = input("rect")->rect;

//        if (depth.empty())
//            return;

//        size(320*2, 240*2);
//        background(backColor);

//        color(tailColor);
//        if (human.isTracking) {
//            draw(tailImage, human.wristRight.x, human.wristRight.y, tailSize, tailSize);
//            draw(tailImage, human.wristLeft.x, human.wristLeft.y, tailSize, tailSize);
//        }
//    }
//};


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

        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->addInput("hit", PortType::Mat);
        scenesNode->addInput("rect", PortType::Rect);
        scenesNode->addInput("human1", PortType::Human);
        scenesNode->addInput("human2", PortType::Human);
        scenesNode->setPos(200, 100);
        scenesNode->addScene(new ShadowScene);
//        scenesNode->addScene(new RaysScene);
//        scenesNode->addScene(new TailHandsScene);
        nodes.append(scenesNode);

        kinectNode->addLink(scenesNode, "hit", "hit");
        kinectNode->addLink(scenesNode, "human1", "human1");
        kinectNode->addLink(scenesNode, "human2", "human2");
        rectNode->addLink(scenesNode, "rect", "rect");
    }
};

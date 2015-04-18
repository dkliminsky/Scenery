#include "nodes/project.h"
#include "nodes/nodes.h"
#include "nodes/graphics/scene.h"


class Example1Scene : public Scene
{
public:
    Image *ship;
    Image stream;
    int ship_size;
    int ship_dx;
    Color back;

    Example1Scene()
    {
        ship = new Image("images/ship_512.png");
        ship_dx = 80;
        control(ship_size=50, "ship_size", 0, 1000);
        button(1, "Left");
        button(2, "Right");
        control(back=Color(1,1,1,0), "Background");
    }

    QString name() { return "Example 1"; }

    void setup(){}

    void resize()
    {
        background(back);
    }

    void paint()
    {
        size(200, 200);
        background(back);
        color(1.0f, 1.0f, 1.0f, 1.0f);

        stream.set(input(0)->mat);
        Rect pos = input(1)->rect;
        draw(&stream, pos.x, pos.y, pos.width, pos.height);
        flush();

        painter()->endNativePainting();
        painter()->fillRect(90, 90, 30, 30, Qt::red);
        QLineF line(10.0, 80.0, 90.0, 20.0);
        painter()->drawLine(line);
        QPainterPath path;
        path.moveTo(20, 80);
        path.lineTo(20, 30);
        path.cubicTo(80, 0, 50, 50, 80, 80);
        painter()->drawPath(path);
        painter()->beginNativePainting();

        draw(ship, ship_dx, 80, ship_size, ship_size);
    }

    void signal(int id) {
        if (id == 1) {
            ship_dx -= 5;
        }
        else if (id == 2) {
            ship_dx += 5;
        }
    }
};


class Example2Scene : public Scene
{
public:
    Image *ship;
    Image stream;
    int ship_size;

    Example2Scene()
    {
        ship = new Image("images/ship_512.png");
        control(ship_size=50, "ship_size", 0, 1000);
    }

    QString name() { return "Example 2"; }

    void setup(){}

    void resize(){}

    void paint()
    {
        size(200, 200);
        color(1.0f, 1.0f, 1.0f, 1.0f);
        stream.set(input(0)->mat);
        draw(&stream, width()/2, height()/2, width(), height());
    }
};



class Manager_ : public Project
{
public:
    void init() {
        Node *cameraNode = new CameraNode();
        cameraNode->setPos(0, 0);
        nodes.append(cameraNode);

        Node *erodeNode = new ErodeNode();
        erodeNode->setPos(300, -100);
        nodes.append(erodeNode);

        Node *dilateNode = new DilateNode();
        dilateNode->setPos(450, 0);
        nodes.append(dilateNode);

        Node *positionNode = new RectNode();
        positionNode->setPos(0, 200);
        nodes.append(positionNode);

        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->inputs.append(new Port(PortType::Rect));
        scenesNode->setPos(200, 100);
        scenesNode->addScene(new Example1Scene());
        scenesNode->addScene(new Example2Scene());
        nodes.append(scenesNode);

        cameraNode->outputs.at(0)->links.append(new Link(erodeNode, 0));
        erodeNode->outputs.at(0)->links.append(new Link(dilateNode, 0));
        dilateNode->outputs.at(0)->links.append(new Link(scenesNode, 0));
        positionNode->outputs.at(0)->links.append(new Link(scenesNode, 1));
    }
};

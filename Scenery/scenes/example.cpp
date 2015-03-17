#include "nodes/manager.h"
#include "nodes/nodes.h"
#include "nodes/graphics/scene.h"


class Example1Scene : public Scene
{
public:
    Image *ship;
    Image stream;
    int ship_size;

    Example1Scene()
    {
        ship = new Image("images/ship_512.png");
        control(ship_size=50, "ship_size", 0, 1000);
    }

    QString name() { return "Example 1"; }

    void setup(){}

    void resize()
    {
        //background(0, 0, 1, 1);
    }

    void paint()
    {
        painter()->beginNativePainting();
        size(200, 200);
        background(1, 1, 1, 0);
        color(1.0f, 1.0f, 1.0f, 1.0f);

        stream.set(input(0)->mat);
        draw(&stream, 50, 50, 100, 100);
//        draw(ship, 80, 80, 50, 50);
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
        draw(ship, 80, 80, ship_size, ship_size);
        painter()->endNativePainting();
    }
};


class Manager_ : public Manager
{
public:
    void init() {
        Node *cameraNode = new CameraNode();
        cameraNode->setPos(0, 0);
        sources.append(cameraNode);
        nodes.append(cameraNode);

        Node *erodeNode = new ErodeNode();
        erodeNode->setPos(300, -100);
        nodes.append(erodeNode);

        Node *dilateNode = new DilateNode();
        dilateNode->setPos(450, 0);
        nodes.append(dilateNode);

        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->setPos(200, 100);
        scenesNode->addScene(new Example1Scene());
        nodes.append(scenesNode);

        cameraNode->outputs.at(0)->links.append(new Link(erodeNode, 0));
        erodeNode->outputs.at(0)->links.append(new Link(dilateNode, 0));
        dilateNode->outputs.at(0)->links.append(new Link(scenesNode, 0));
    }
};

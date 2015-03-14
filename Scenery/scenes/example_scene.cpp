#include "nodes/manager.h"
#include "nodes/nodes.h"
#include "nodes/graphics/scene.h"


class DefaultScene : public Scene
{
public:
    DefaultScene();

    QString name() { return "Welcome"; }

    void setup();
    void resize();
    void paint();

private:
    QImage ship;
//    Image *imageShip;
//    Image *imageStream;

};


DefaultScene::DefaultScene() :
    ship("images/ship_512.png")
{
}

void DefaultScene::setup()
{
//    imageShip = new Image("resources/images/ship.png");
//    imageShip->bind();

//    imageStream = new Image();
}

void DefaultScene::resize()
{
//    background(1, 1, 1, 1);
}

void DefaultScene::paint()
{
    size(640, 480);
    //background(1, 1, 0.5, 0.5);

    Mat &mat = input(0)->mat;

    if (mat.rows) {
        Mat image;
        cvtColor(mat, image, CV_BGR2RGB);
        QImage stream = QImage(image.data, image.cols, image.rows, QImage::Format_RGB888);
        painter()->drawImage(0, 0, stream);
    }

    painter()->fillRect(40, 40, 200, 200, Qt::red);
    painter()->fillRect(0, 0, 128, 128, Qt::green);
//    QImage i = QImage("images/ship_512.png");
    painter()->drawImage(0, 0, ship);



    //    size(200, 200);
//    background(1, 1, 1, 1);

//    color(1, 1, 1, 1);
//    image(imageShip, 50, 50, 90, 90);

//    imageStream->set(process(0)->mat);
//    imageStream->bind();

//    image(imageStream, 150, 150, 90, 90);
}



class ExampleManager : public Manager
{
public:
    void initScene() {
        Node *cameraNode = new CameraNode();
        cameraNode->setPos(0, 0);
        sources.append(cameraNode);
        nodes.append(cameraNode);

//        Node *colorNode = new ColorNode();
//        colorNode->setPos(150, 0);
//        nodes.append(colorNode);

        Node *erodeNode = new ErodeNode();
        erodeNode->setPos(300, -100);
        nodes.append(erodeNode);

        Node *dilateNode = new DilateNode();
        dilateNode->setPos(450, 0);
        nodes.append(dilateNode);

    //    Node *debugNode1 = new DebugNode();
    //    debugNode1->setPos(200, 50);
    //    nodes.append(debugNode1);

    //    Node *debugNode2 = new DebugNode();
    //    debugNode2->setPos(600, 0);
    //    nodes.append(debugNode2);

        Scene *scene = new DefaultScene();
        ScenesNode *scenesNode = new ScenesNode();
        scenesNode->inputs.append(new Port(PortType::Mat));
        scenesNode->setPos(200, 100);
        scenesNode->setScene(scene);
        nodes.append(scenesNode);


//        cameraNode->outputs.at(0)->links.append(new Link(colorNode, 0));
        cameraNode->outputs.at(0)->links.append(new Link(erodeNode, 0));
        erodeNode->outputs.at(0)->links.append(new Link(dilateNode, 0));
    //    dilateNode->outputs.at(0)->links.append(new Link(debugNode2, 0));
        dilateNode->outputs.at(0)->links.append(new Link(scenesNode, 0));
        //dilateNode->outputs.at(0)->links.append(new Link(viewNode, 0));
    }
};

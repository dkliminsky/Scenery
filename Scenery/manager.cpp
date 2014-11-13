#include "debug.h"
#include "manager.h"
#include "process/process.h"


Manager::Manager(QObject *parent) :
    QObject(parent)
{
    METHOD_BEGIN

//    ProcessTools::initRGB2HSV();
    initScene();
    startTimer(17);

    METHOD_END
}

Manager::~Manager()
{
    METHOD_BEGIN

    foreach (Node *node, nodes) {
        node->process_wait();
        delete node;
    }

    METHOD_END
}

void Manager::timerEvent(QTimerEvent *)
{
    foreach (Node *node, sources) {
        node->process();
    }
}

void Manager::initScene()
{
    Node *cameraNode = new CameraNode();
    cameraNode->setPos(0, 0);
    sources.append(cameraNode);
    nodes.append(cameraNode);

    Node *colorNode = new ColorNode();
    colorNode->setPos(200, 0);
    nodes.append(colorNode);

    Node *debugNode1 = new DebugNode();
    debugNode1->setPos(400, 0);
    nodes.append(debugNode1);

    Node *debugNode2 = new DebugNode();
    debugNode2->setPos(200, 50);
    nodes.append(debugNode2);

    cameraNode->out.at(0)->links.append(new Link(debugNode1, 0));
    cameraNode->out.at(0)->links.append(new Link(colorNode, 0));

    colorNode->out.at(0)->links.append(new Link(debugNode2, 0));

}

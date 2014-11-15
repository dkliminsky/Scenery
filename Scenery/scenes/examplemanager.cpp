#include "examplemanager.h"


void ExampleManager::initScene()
{
    Node *cameraNode = new CameraNode();
    cameraNode->setPos(0, 0);
    sources.append(cameraNode);
    nodes.append(cameraNode);

    Node *colorNode = new ColorNode();
    colorNode->setPos(200, 0);
    nodes.append(colorNode);

    Node *debugNode1 = new DebugNode();
    debugNode1->setPos(200, 50);
    nodes.append(debugNode1);

    Node *debugNode2 = new DebugNode();
    debugNode2->setPos(400, 0);
    nodes.append(debugNode2);

    cameraNode->out.at(0)->links.append(new Link(debugNode1, 0));
    cameraNode->out.at(0)->links.append(new Link(colorNode, 0));
    colorNode->out.at(0)->links.append(new Link(debugNode2, 0));

    QGLFormat format;
    format.setDoubleBuffer(false);
    viewNode = new ViewNode(format);
    viewNode->in.append(new Port(PortType::Mat));
    viewNode->setPos(200, 100);
    viewNode->setScene(new DefaultScene);
    nodes.append(viewNode);

    cameraNode->out.at(0)->links.append(new Link(viewNode, 0));
}

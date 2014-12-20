#include "examplemanager.h"


void ExampleManager::initScene()
{
    Node *cameraNode = new CameraNode();
    cameraNode->setPos(0, 0);
    sources.append(cameraNode);
    nodes.append(cameraNode);

//    Node *colorNode = new ColorNode();
//    colorNode->setPos(150, 0);
//    nodes.append(colorNode);

//    Node *erodeNode = new ErodeNode();
//    erodeNode->setPos(300, 0);
//    nodes.append(erodeNode);

//    Node *dilateNode = new DilateNode();
//    dilateNode->setPos(450, 0);
//    nodes.append(dilateNode);


//    Node *debugNode1 = new DebugNode();
//    debugNode1->setPos(200, 50);
//    nodes.append(debugNode1);

//    Node *debugNode2 = new DebugNode();
//    debugNode2->setPos(600, 0);
//    nodes.append(debugNode2);

//    cameraNode->outputs.at(0)->links.append(new Link(colorNode, 0));
//    colorNode->outputs.at(0)->links.append(new Link(erodeNode, 0));
//    erodeNode->outputs.at(0)->links.append(new Link(dilateNode, 0));
//    //dilateNode->outputs.at(0)->links.append(new Link(debugNode2, 0));

    ViewNode *viewNode = new ViewNode();
    viewNode->inputs.append(new Port(PortType::Mat));
    viewNode->setPos(200, 100);
    viewNode->setScene(new DefaultScene);
    nodes.append(viewNode);

    cameraNode->outputs.at(0)->links.append(new Link(viewNode, 0));
    //dilateNode->outputs.at(0)->links.append(new Link(viewNode, 0));
}

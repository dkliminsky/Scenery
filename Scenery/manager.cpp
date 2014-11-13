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
    sources.append(cameraNode);
    nodes.append(cameraNode);

    Node *debugNode1 = new DebugNode();
    debugNode1->setPos(200, 0);
    nodes.append(debugNode1);

    Node *debugNode2 = new DebugNode();
    debugNode2->setPos(200, 50);
    nodes.append(debugNode2);

    cameraNode->out.at(0)->links.append(new Link(debugNode1, 0));
    cameraNode->out.at(0)->links.append(new Link(debugNode2, 0));
}

//Manager::~Manager()
//{
//    qDebug() << "Manager: Destructor begin";

//    for ( int i=0; i<processes.size(); i++){
//        processes[i]->wait();
//        delete processes[i];
//    }

//    for ( int i=0; i<inputs.size(); i++){
//        inputs[i]->wait();
//        delete inputs[i];
//    }

//    for ( int i=0; i<views.size(); i++){
//        delete views[i];
//    }

//    for ( int i=0; i<scenes.size(); i++){
//        delete scenes[i];
//    }

//    qDebug() << "Manager: Destructor begin";
//}

//void Manager::processesStart()
//{
//    for (int i=0; i<processes.size(); i++)
//        processes.at(i)->start();
//}

//void Manager::processesCopyData()
//{
//    for (int i=0; i<processes.size(); i++)
//        processes.at(i)->copyData();
//}

//bool Manager::isProcessesComplete()
//{
//    for (int i=0; i<processes.size(); i++)
//        if (processes.at(i)->isRunning())
//            return false;
//    return true;
//}

//bool Manager::isInputsComplete()
//{
//    for (int i=0; i<inputs.size(); i++)
//        if (inputs.at(i)->isRunning())
//            return false;
//    return true;
//}


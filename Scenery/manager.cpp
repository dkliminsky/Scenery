#include "manager.h"
#include "process/process.h"
#include <QDebug>

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Manager: Constructor begin";

//    ProcessTools::initRGB2HSV();

    Node *cameraNode = new CameraNode();
    sources.append(cameraNode);

    Node *bebugNode = new DebugNode();
    sources.append(bebugNode);

    cameraNode->out.at(0)->node = bebugNode;

    startTimer(17);
    qDebug() << "Manager: Constructor end";
}

Manager::~Manager()
{
    qDebug() << "Manager: Destructor begin";

    foreach (Node *node, sources) {
        node->process_wait();
        delete node;
    }

    qDebug() << "Manager: Destructor end";
}

void Manager::timerEvent(QTimerEvent *)
{
    foreach (Node *node, sources) {
        processNode(node);
    }
}

void Manager::processNode(Node *node)
{
    if (!node->isProcessing()) {
        foreach (Link *link, node->out) {
            if (link->node && !link->node->isProcessing()) {
                link->node->in.at(0)->mat = link->mat.clone();
                processNode(link->node);
            }
        }
        node->process();
    }
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


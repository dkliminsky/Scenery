#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Manager: Constructor begin";

    ProcessTools::initRGB2HSV();

    qDebug() << "Manager: Constructor end";
}

Manager::~Manager()
{
    qDebug() << "Manager: Destructor begin";

    for ( int i=0; i<processes.size(); i++){
        processes[i]->wait();
        delete processes[i];
    }

    for ( int i=0; i<inputs.size(); i++){
        inputs[i]->wait();
        delete inputs[i];
    }

    for ( int i=0; i<views.size(); i++){
        delete views[i];
    }

    for ( int i=0; i<scenes.size(); i++){
        delete scenes[i];
    }

    qDebug() << "Manager: Destructor begin";
}

void Manager::processesStart()
{
    for (int i=0; i<processes.size(); i++)
        processes.at(i)->start();
}

void Manager::processesCopyData()
{
    for (int i=0; i<processes.size(); i++)
        processes.at(i)->copyData();
}

bool Manager::isProcessesComplete()
{
    for (int i=0; i<processes.size(); i++)
        if (processes.at(i)->isRunning())
            return false;
    return true;
}

bool Manager::isInputsComplete()
{
    for (int i=0; i<inputs.size(); i++)
        if (inputs.at(i)->isRunning())
            return false;
    return true;
}


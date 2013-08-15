#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    ProcessTools::initRGB2HSV();
}

Manager::~Manager()
{
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
}

void Manager::processesStart()
{
    for (int i=0; i<processes.size(); i++)
        processes.at(i)->start();
}

bool Manager::isProcessesComplete()
{
    for (int i=0; i<processes.size(); i++)
        if (processes.at(i)->isRunning())
            return false;
    return true;
}


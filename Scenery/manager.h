#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

#include "process/node.h"
#include "process/process.h"


//#include "process/process.h"
//#include "process/input.h"
//#include "graphics/view.h"
//#include "graphics/scene.h"

//typedef QVector<Process *> Processes;
//typedef QVector<Input *>   Inputs;
//typedef QVector<View *>    Views;
//typedef QVector<Scene *>   Scenes;

typedef QList<Node *> Nodes;

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

    Nodes sources;

protected:
    void timerEvent(QTimerEvent *);


//    ~Manager();

//    virtual QString name() = 0;

//    Processes &getProcesses() { return processes; }
//    Inputs    &getInputs()    { return inputs; }
//    Scenes    &getScenes()    { return scenes; }
//    Views     &getViews()     { return views; }

//    void processesStart();
//    void processesCopyData();
//    bool isProcessesComplete();
//    bool isInputsComplete();

//protected:
//    virtual void timerEvent(QTimerEvent *) = 0;

//    Processes processes;
//    Inputs    inputs;
//    Views     views;
//    Scenes    scenes;

//signals:
    
//public slots:
    
};

#endif // MANAGER_H

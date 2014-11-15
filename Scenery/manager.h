#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "process/node.h"
#include "process/graphics/viewnode.h"


class Manager : public QObject
{
	Q_OBJECT

public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

    Nodes sources;
    Nodes nodes;

protected:
    void timerEvent(QTimerEvent *);

private:
    void initScene();
    ViewNode *viewNode;
    
};

#endif // MANAGER_H

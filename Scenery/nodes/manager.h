#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "nodes/node.h"


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
    virtual void init() = 0;
    
};

#endif // MANAGER_H

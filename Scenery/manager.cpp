#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    QGLFormat format;
    format.setDoubleBuffer(false);
    view = new View(format);
    view->setScene(new Skeleton());
    startTimer(17);
}

Manager::~Manager()
{
    delete view;
}

void Manager::timerEvent(QTimerEvent *)
{
    view->updateGL();
}

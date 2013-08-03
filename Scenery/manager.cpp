#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent) :
    QObject(parent)
{
    QGLFormat format;
    format.setDoubleBuffer(false);
    view = new View(format);
    //view->setScene(new Skeleton());
    view->setScene(new Cage());
    //view->setScene(new Brush());

    view->datas()->resize(1);
    view->datas()->at(0).width = 640;
    view->datas()->at(0).height = 480;

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

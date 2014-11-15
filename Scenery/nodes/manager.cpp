#include "debug.h"
#include "manager.h"


Manager::Manager(QObject *parent) :
    QObject(parent)
{
    METHOD_BEGIN

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

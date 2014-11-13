#include "node.h"
#include "debug.h"

Node::Node() :
    _posX(0),
    _posY(0)
{
    METHOD_BEGIN

    time.start();
    timeMean = 0;
    timeNum = 0;
    timeResult = 0;

    METHOD_END
}

void Node::process()
{
    timing_start();
    _process();
    timing_finish();
    processNext();
}

void Node::processNext()
{
    foreach (Port *port, out) {
        foreach (Link *link, port->links) {
            Node *next = link->node;

            Q_ASSERT(next);
            Q_ASSERT(next->in.count() > link->port_id);

            if (!next->isProcessing()) {
                next->in.at(link->port_id)->mat = port->mat.clone();
                next->process();
            }
        }
    }
}

void Node::timing_start()
{
    time.restart();
}

void Node::timing_finish()
{
    timeMean += time.elapsed();
    timeNum++;
    if ( timeNum == 10 ) {
        timeResult = timeMean/10;
        timeMean = 0;
        timeNum = 0;

        qDebug() << name() << timeResult;
    }
}

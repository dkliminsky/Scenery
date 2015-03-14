#include "node.h"
#include "debug.h"

Node::Node() :
    _uuid(QUuid::createUuid()),
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

Node::~Node()
{
    foreach (IControl *control, controls) {
        delete control;
    }
}

void Node::processNext()
{
    foreach (Port *port, outputs) {
        foreach (Link *link, port->links) {
            Node *next = link->node;

            Q_ASSERT(next);
            Q_ASSERT(next->inputs.count() > link->port_id);

            if (!next->isProcessing()) {
                next->inputs.at(link->port_id)->mat = port->mat.clone();
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

        //qDebug() << name() << timeResult;
    }
}

void Node::input(PortType type)
{
    inputs.append(new Port(type));
}

void Node::output(PortType type)
{
    outputs.append(new Port(type));
}

void Node::control(int &x, QString description, int min, int max, int step)
{
    controls += new ControlInt(x, description, min, max, step);
}

void Node::control(double &x, QString description, double min, double max, int precision)
{
    controls += new ControlDouble(x, description, min, max, precision);
}

void Node::control(bool &x, QString description)
{
    controls += new ControlBool(x, description);
}

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

}

QJsonObject Node::getJson()
{
    QJsonObject json;
    json["uuid"] = uuid();
    json["name"] = name();
    json["posX"] = posX();
    json["posY"] = posY();
    json["control"] = getControlJson();
    return json;
}

void Node::setJson(QJsonObject json)
{
    setPos(json["posX"].toInt(), json["posY"].toInt());
    setControlJson(json["control"].toObject());
}

void Node::processNext()
{
    foreach (Port *port, outputs) {
        foreach (Link *link, port->links) {
            Node *next = link->node;
            Q_ASSERT(next);
            Q_ASSERT(next->outputs()->contains(link->portName));

            if (!next->isProcessing()) {
                next->input(link->portName)->mat = port->mat.clone();
                next->input(link->portName)->human = port->human;
                next->input(link->portName)->rect = port->rect;
                next->input(link->portName)->booleans = port->booleans;
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

void Node::addInput(QString name, PortType type)
{
    inputs.insert(name, new Port(name, type));
}

void Node::addOutput(QString name, PortType type)
{
    outputs.insert(name, new Port(name, type));
}

void Node::addLink(Node *node, QString outputName, QString inputName)
{
    qDebug() << "Add link, node:" << node->name() << "output:" << outputName << "input:" << inputName;
    output(outputName)->links.append(new Link(node, inputName));
}

Port *Node::input(QString name)
{
    if (!inputs.contains(name))
        qDebug() << "Not found input" << name;
    return inputs.value(name);
}

Port *Node::output(QString name)
{
    if (!outputs.contains(name))
        qDebug() << "Not found output" << name;
    return outputs.value(name);
}

bool Node::isOutputLink(QString name)
{
    if (output(name)->links.size())
        return true;
    return false;
}


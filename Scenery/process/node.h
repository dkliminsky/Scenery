#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QTime>
#include <QThread>
#include <opencv2/opencv.hpp>
#include "debug.h"


using namespace cv;

class Node;
class Port;
class Link;

typedef QList<Link *> Links;
typedef QList<Port *> Ports;
typedef QList<Node *> Nodes;

enum class PortType { Mat, Human };


class Link
{
public:
    Link(Node *node, int port_id) : node(node), port_id(port_id)  {}
    Node *node;
    int port_id;
};

class Port
{
public:
    Port(PortType type) : type(type) {}
    PortType type;
    Links links;

    // Data
    Mat mat;
    vector<Rect> rects;
    // ...
};

class Node
{
public:
    Node();
    virtual ~Node() {}

    virtual const QString name() { return QString("Noname"); }
    virtual const QString tooltip() { return "Node"; }

    int posX() { return _posX; }
    int posY() { return _posY; }
    void setPos(int x, int y) { _posX = x; _posY = y; }

    int timing() { return timeResult; }

    virtual void process();
    virtual void process_wait() {}
    virtual bool isProcessing() { return false; }

    Ports in;
    Ports out;

protected:
    int _posX;
    int _posY;

    virtual void run() {}
    virtual void _process() { run(); }

    void processNext();
    void timing_start();
    void timing_finish();

private:
    QTime time;
    int timeMean;
    int timeNum;
    int timeResult;

};


class ThreadNode: public Node, public QThread
{
public:
    ThreadNode() {}
    virtual ~ThreadNode() {}

    virtual void process_wait() override final { wait(); }
    virtual bool isProcessing() override final { return isRunning(); }

protected:
    virtual void _process() override final { start(); }

};

#endif // NODE_H

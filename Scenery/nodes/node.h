#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QString>
#include <QTime>
#include <QThread>
#include <QUuid>
#include <opencv2/core/core.hpp>
#include "debug.h"
#include "controls/controlprovider.h"
#include "kinect/human.h"
using namespace cv;

class Node;
class Port;
class Link;

typedef QList<Link *> Links;
typedef QList<Port *> Ports;
typedef QList<Node *> Nodes;

enum class PortType { Mat, Human, Boolean, Booleans, Number, Numbers, Rect, Rects };


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
    void *data;

    Mat mat;

    Human human;
    vector<Human> humans;

    bool boolean;
    vector<bool> booleans;

    int number;
    vector<int> numbers;

    Rect rect;
    vector<Rect> rects;
    // ...
};

class Node: public ControlProvider
{
public:
    Node();
    virtual ~Node();

    virtual const QString name() { return QString("Noname"); }
    virtual const QString tooltip() { return "Node"; }
    virtual bool isSource() { return false; }
    virtual QWidget *widget() { return nullptr; }

    QString uuid() { return _uuid.toString(); }
    int posX() { return _posX; }
    int posY() { return _posY; }
    void setPos(int x, int y) { _posX = x; _posY = y; }

    int timing() { return timeResult; }

    virtual void process() { timing_start();
                             run();
                             timing_finish();
                             processNext();}
    virtual void process_wait() {}
    virtual bool isProcessing() { return false; }

    Ports inputs;
    Ports outputs;

protected:
    virtual void run() {}
    void processNext();
    void timing_start();
    void timing_finish();

    void input(PortType type);
    void output(PortType type);

private:
    QUuid _uuid;
    int _posX;
    int _posY;

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

    virtual void process() { timing_start();
                             start();
                             timing_finish();
                             processNext();}
    virtual void process_wait() override final { wait(); }
    virtual bool isProcessing() override final { return isRunning(); }

protected:
    virtual void run() {}
};

#endif // NODE_H

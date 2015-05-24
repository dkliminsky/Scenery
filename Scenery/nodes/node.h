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
typedef QHash<QString, Port *> Ports;
typedef QList<Node *> Nodes;

enum class PortType { Mat, Human, Boolean, Booleans, Number, Numbers, Rect, Rects };


class Link
{
public:
    Link(Node *node, QString portName) : node(node), portName(portName)  {}
    Node *node;
    QString portName;
};

class Port
{
public:
    Port(QString name, PortType type) : _name(name), type(type) {}
    const QString name() { return _name; }

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

private:
    QString _name;
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

    virtual QJsonObject getJson();
    virtual void setJson(QJsonObject json);

    void addInput(QString name, PortType type);
    void addOutput(QString name, PortType type);
    void addLink(Node *node, QString outputName, QString inputName);

    Port *input(QString name);
    Port *output(QString name);

    bool isOutputLink(QString name);

    Ports inputs;
    Ports outputs;

protected:
    virtual void run() {}
    void processNext();
    void timing_start();
    void timing_finish();

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

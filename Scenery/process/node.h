#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QThread>
#include <opencv2/opencv.hpp>

using namespace cv;

class Node;

enum class LinkType { Mat, Human };


class Link
{
public:
    Link(LinkType type) : type(type), node(nullptr) {}

    LinkType type;
    Node *node;
    int in;
    int out;

    Mat mat;
};

typedef QList<Node *> Nodes;
typedef QList<Link *> Links;


class Node
{
public:
    Node() : _posX(0), _posY(0) {}
    virtual ~Node() {}

    virtual const QString name() { return QString("Noname"); }
    virtual const QString tooltip() { return "Node"; }

    int posX() { return _posX; }
    int posY() { return _posY; }
    void setPos(int x, int y) { _posX = x; _posY = y; }

    virtual void process() { run(); }
    virtual void process_wait() {}
    virtual bool isProcessing() { return false; }

    Links in;
    Links out;

protected:
    int _posX;
    int _posY;

    virtual void run() {}
};


class ThreadNode: public Node, public QThread
{
public:
    ThreadNode() {}
    virtual ~ThreadNode() {}

    virtual void process() override final { start(); }
    virtual void process_wait() override final { wait(); }
    virtual bool isProcessing() override final { return isRunning(); }
};

#endif // NODE_H

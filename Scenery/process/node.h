#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QThread>


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

    virtual void process() { run(); }

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
    virtual void process() { start(); }
};

#endif // NODE_H

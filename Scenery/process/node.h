#ifndef NODE_H
#define NODE_H

#include <QString>


class Node
{
public:
    Node(int _posX=0, int _posY=0);

    const QString &name() { return _name; }
    const QString &tooltip() { return _tooltip; }

    int posX() { return _posX; }
    int posY() { return _posY; }
    int setPos(int x, int y) { _posX = x; _posY = y; }

protected:
    QString _name;
    QString _tooltip;

    int _posX;
    int _posY;

};

#endif // NODE_H

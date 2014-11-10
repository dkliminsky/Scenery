#ifndef NODE_H
#define NODE_H

#include <QString>


class Node
{
public:
    Node();

    const QString &getName() { return name; }
    const QString &getTooltip() { return tooltip; }

    int getPosX() { return posX; }
    int getPosY() { return posY; }

protected:
    QString name;
    QString tooltip;

    int posX;
    int posY;

};

#endif // NODE_H

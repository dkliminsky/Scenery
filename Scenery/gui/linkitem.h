#ifndef LINKITEM_H
#define LINKITEM_H

#include <QGraphicsItem>
#include "nodes/node.h"

class LinkItem;
typedef QList<LinkItem *> LinkItems;


class LinkItem : public QGraphicsItem
{
public:
    LinkItem(Node *node_from, Node *node_to);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void repaint();

    QRect calcRect() const;

private:
    Node *node_from;
    Node *node_to;
};

#endif // LINKITEM_H

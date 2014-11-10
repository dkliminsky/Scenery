#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>

#include "process/node.h"


class NodeItem : public QGraphicsItem
{
public:
    NodeItem(Node *_node);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Node *node;

};

#endif // NODEITEM_H

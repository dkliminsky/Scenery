#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>
#include "nodes/node.h"
#include "linkitem.h"
#include "controls/controlwidgets.h"


class NodeItem : public QGraphicsItem
{
public:
    NodeItem(Node *node);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    LinkItems links_out;
    LinkItems links_in;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

private:
    Node *node;
    QWidget widget;

    int width;
    int height;

    void createWidget();

};

#endif // NODEITEM_H

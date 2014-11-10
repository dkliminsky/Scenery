#include <QtWidgets>

#include "nodeitem.h"


NodeItem::NodeItem(Node *node) :
    node(node)
{
    setToolTip("Node");
    setCursor(Qt::OpenHandCursor);
}

QRectF NodeItem::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(-12, -12, 30, 30);

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-15, -15, 30, 30);

    painter->drawText(QPoint(0, 0), "Node");
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

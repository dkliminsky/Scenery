#include <QtWidgets>
#include "debug.h"
#include "linkitem.h"


LinkItem::LinkItem(Node *node_from, Node *node_to) :
    node_from(node_from),
    node_to(node_to)
{
    METHOD_BEGIN

    repaint();

    METHOD_END
}

QRectF LinkItem::boundingRect() const
{
    return bound;
}

void LinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawLine(mapFromScene(node_from->posX(), node_from->posY()),
                      mapFromScene(node_to->posX(),   node_to->posY()));

//    painter->drawRect(bound);
}

void LinkItem::repaint()
{
    prepareGeometryChange();

    QRectF rect = calcBound();
    bound = QRectF(- rect.width() / 2, - rect.height() / 2,
                     rect.width(),   rect.height());
    setPos(rect.x() + rect.width() / 2,
           rect.y() + rect.height() / 2);

    //qDebug() << "bound:" << bound.x() << bound.y() << bound.width() << bound.height();
    //qDebug() << "pos:" << pos();
}

QRectF LinkItem::calcBound() const
{
    float x1 = qMin(node_from->posX(), node_to->posX());
    float y1 = qMin(node_from->posY(), node_to->posY());
    float x2 = qMax(node_from->posX(), node_to->posX());
    float y2 = qMax(node_from->posY(), node_to->posY());
    return QRectF(x1, y1, x2 - x1, y2 - y1);
}

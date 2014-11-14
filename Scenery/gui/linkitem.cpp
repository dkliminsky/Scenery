#include <QtWidgets>
#include "debug.h"
#include "linkitem.h"


LinkItem::LinkItem(Node *node_from, Node *node_to) :
    node_from(node_from),
    node_to(node_to)
{
    METHOD_BEGIN

    QRect rect = calcRect();
    setPos(rect.x() + rect.width() / 2,
           rect.y() + rect.height() / 2);

//    qDebug() << "POS:" << rect().x() + rect().width() / 2 << rect().y() + rect().height() / 2;

    METHOD_END
}

QRectF LinkItem::boundingRect() const
{
    QRect rect = calcRect();
    return QRectF(-rect.width() / 2, -rect.height() / 2,
                   rect.width() / 2,  rect.height() / 2);
}

void LinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRect rect = calcRect();
    if (node_from->posY() <= node_to->posY()) {
        painter->drawLine(-rect.width() / 2, -rect.height() / 2,
                           rect.width() / 2,  rect.height() / 2);
    }
    else {
        painter->drawLine(-rect.width() / 2,  rect.height() / 2,
                           rect.width() / 2, -rect.height() / 2);
    }
}

void LinkItem::repaint()
{
    prepareGeometryChange();
    QRect rect = calcRect();
    setPos(rect.x() + rect.width() / 2,
           rect.y() + rect.height() / 2);
//    update(-rect.width() / 2, -rect.height() / 2,
//            rect.width() / 2,  rect.height() / 2);
//    update(rect.x(), rect.y(),
//           rect.x() + 200, rect.y() + 200);
    //update(0, 0, rect.width(), rect.height());
}

QRect LinkItem::calcRect() const
{
    int x1 = qMin(node_from->posX(), node_to->posX());
    int y1 = qMin(node_from->posY(), node_to->posY());
    int x2 = qMax(node_from->posX(), node_to->posX());
    int y2 = qMax(node_from->posY(), node_to->posY());
    return QRect(x1, y1, x2 - x1, y2 - y1);
}

#include <QtWidgets>
#include "debug.h"
#include "nodeitem.h"


NodeItem::NodeItem(Node *node) :
    node(node)
{
    METHOD_BEGIN

    setToolTip("Node");
    setCursor(Qt::OpenHandCursor);

    width = 80;
    height = 30;
    setPos(node->posX(), node->posY());
    setZValue(1);

    createWidget();

    METHOD_END
}

NodeItem::~NodeItem()
{
    delete widget;
}

QRectF NodeItem::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(2, 2, width, height);

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(0, 0, width - 2, height - 2);

    painter->drawText(QPoint(3, 15), node->name());
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::ClosedHandCursor);
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance()) {
        return;
    }

    setCursor(Qt::OpenHandCursor);
    node->setPos(event->scenePos().x() - event->buttonDownPos(Qt::LeftButton).x(),
                 event->scenePos().y() - event->buttonDownPos(Qt::LeftButton).y());
    setPos(node->posX(), node->posY());

    foreach (LinkItem *linkItem, links_out) {
        linkItem->repaint();
    }

    foreach (LinkItem *linkItem, links_in) {
        linkItem->repaint();
    }
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    widget->show();
}

void NodeItem::createWidget()
{
    if (node->widget()) {
        widget = node->widget();
    }
    else {
        widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        widget->setLayout(layout);

        if (!node->controls.empty()) {
            layout->addWidget(make_controls_widget(&node->controls));
        }
    }

    widget->setWindowTitle(node->name());
}

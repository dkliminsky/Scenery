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
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    widget.show();
}

void NodeItem::createWidget()
{
    if (node->controls.empty())
        return;

    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    for(int i=0; i<node->controls.size(); i++) {
        IControl *control = node->controls.at(i);
        layout->addWidget(new QLabel(control->name()), i, 0);
        layout->addWidget(control_widget_factory(control), i, 1);
    }
    layout->setRowStretch(layout->count()-1, 1);
    widget.setLayout(layout);
    widget.setWindowTitle(node->name());
}

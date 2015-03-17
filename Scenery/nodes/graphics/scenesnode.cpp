#include "scenesnode.h"

#include "gui/controls/controlwidgets.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>


ScenesNode::ScenesNode() :
    _scene(nullptr)
{
    startTimer(17);
    createWidget();
}

ScenesNode::~ScenesNode()
{

}

void ScenesNode::addScene(Scene *scene)
{
    _scene = scene;
    _scene->_inputs = &inputs;
    _view.setScene(scene);

    QTableWidgetItem *sceneItem = new QTableWidgetItem(scene->name());
    scenesTable->setItem(0, 0, sceneItem);
    scenesTable->resizeRowsToContents();
    scenesTable->resizeColumnsToContents();

    QWidget *controlsWidget = new QWidget;
    controlsWidget->setLayout(make_controls_layout(&scene->_controls));
    controlsStacked->addWidget(controlsWidget);
}

void ScenesNode::timerEvent(QTimerEvent *)
{
    _view.update();
}

void ScenesNode::createWidget()
{
    _widget = new QWidget();
    scenesTable = new QTableWidget(1, 1);
    controlsStacked = new QStackedWidget;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(scenesTable);
    layout->addWidget(controlsStacked);
    _widget->setLayout(layout);
}


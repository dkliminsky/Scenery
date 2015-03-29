#include "scenesnode.h"

#include "gui/controls/controlwidgets.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>


ScenesNode::ScenesNode() :
    curScene(nullptr)
{
    startTimer(17);
    createWidget();
}

ScenesNode::~ScenesNode()
{

}

void ScenesNode::addScene(Scene *scene)
{
    if (!curScene) {
        setCurScene(scene);
    }

    _scenes.append(scene);
    scene->_inputs = &inputs;

    QTableWidgetItem *sceneItem = new QTableWidgetItem(scene->name());
    scenesTable->setRowCount(_scenes.size());
    scenesTable->setItem(_scenes.size()-1, 0, sceneItem);

    controlsStacked->addWidget(make_controls_widget(&scene->_controls));
}

void ScenesNode::setCurScene(Scene *scene)
{
    curScene = scene;
    _view.setScene(scene);
    qDebug() << "Set scene:" << scene->name();
}

void ScenesNode::timerEvent(QTimerEvent *)
{
    _view.update();
}

void ScenesNode::createWidget()
{
    _widget = new QWidget();
    QPushButton *button = new QPushButton("&Full");
    scenesTable = new QTableWidget(2, 1);
    controlsStacked = new QStackedWidget;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(button);
    layout->addWidget(scenesTable);
    layout->addWidget(controlsStacked);
    _widget->setLayout(layout);

    connect(scenesTable, SIGNAL(cellDoubleClicked(int,int)),
            this, SLOT(slotChangeScene(int,int)));

    connect(button, SIGNAL(clicked(bool)), this, SLOT(slotFullScreen(bool)));
}

void ScenesNode::slotFullScreen(bool isFull)
{
    _view.showFullScreen();

//    if (isFull) {
//        _view.showFullScreen();
//    }
//    else {
//        _view.showNormal();
//    }
}

void ScenesNode::slotChangeScene(int row, int column)
{
    if ( column == 0) {
       setCurScene(_scenes.at(row));
       controlsStacked->setCurrentIndex(row);
   }
}


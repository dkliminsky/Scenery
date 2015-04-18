#include "scenesnode.h"

#include "gui/controls/controlwidgets.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QAction>


ScenesNode::ScenesNode() :
    curScene(nullptr)
{
    createWidget();
    createActions();
    createToolBars();

    startTimer(17);
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
    _widget = new QMainWindow();
    scenesTable = new QTableWidget(2, 1);
    controlsStacked = new QStackedWidget;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(scenesTable);
    layout->addWidget(controlsStacked);
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    _widget->setCentralWidget(centralWidget);

    connect(scenesTable, SIGNAL(cellDoubleClicked(int,int)),
            this, SLOT(slotChangeScene(int,int)));
}

void ScenesNode::createActions()
{
    fullAct = new QAction(QIcon(":/icons/resources/icons/fullscreen.png"),
                          tr("&Full Screen"), this);
    fullAct->setCheckable(true);
    connect(fullAct, SIGNAL(triggered(bool)), this, SLOT(slotFullScreen(bool)));
}

void ScenesNode::createToolBars()
{
    sceneToolBar = _widget->addToolBar(tr("Scene"));
    sceneToolBar->addAction(fullAct);
}

void ScenesNode::slotFullScreen(bool isFull)
{
    if (isFull) {
        _view.showFullScreen();
    }
    else {
        _view.showNormal();
    }
}

void ScenesNode::slotChangeScene(int row, int column)
{
    if ( column == 0) {
       setCurScene(_scenes.at(row));
       controlsStacked->setCurrentIndex(row);
   }
}


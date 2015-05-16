#include "scenesnode.h"

#include "gui/controls/controlwidgets.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QAction>
#include <QJsonObject>
#include <QJsonArray>


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
    if (_scenes.contains(scene->name())) {
        qDebug() << "Double scene name!!";
        return;
    }

    if (!curScene) {
        setCurScene(scene);
    }

    _scenes.insert(scene->name(), scene);
    scene->_inputs = &inputs;

    QTableWidgetItem *sceneItem = new QTableWidgetItem(scene->name());
    scenesTable->setRowCount(_scenes.size());
    scenesTable->setItem(_scenes.size()-1, 0, sceneItem);

    controlsStacked->addWidget(make_controls_widget(&scene->controls()));
}

void ScenesNode::setCurScene(Scene *scene)
{
    curScene = scene;
    _view.setScene(scene);
    qDebug() << "Set scene:" << scene->name();
}

QJsonObject ScenesNode::getJson()
{
    QJsonObject json = Node::getJson();
    QJsonArray scenesArray;
    foreach(Scene *scene, _scenes) {
        QJsonObject sceneObject;
        sceneObject["name"] = scene->name();
        sceneObject["control"] = scene->getControlJson();
        scenesArray.append(sceneObject);
    }
    json["scenes"] = scenesArray;
    return json;
}

void ScenesNode::setJson(QJsonObject json)
{
    QJsonArray scenesArray = json["scenes"].toArray();
    for(int i=0; i<scenesArray.size(); i++) {
        QJsonObject sceneObject = scenesArray[i].toObject();
        QJsonObject controlObject = sceneObject["control"].toObject();
        QString name = sceneObject["name"].toString();
        if (_scenes.contains(name)) {
            _scenes[name]->setControlJson(controlObject);
        }
    }
    Node::setJson(json);
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
        QTableWidgetItem *item = scenesTable->item(row, column);
       setCurScene(_scenes.value(item->text()));
       controlsStacked->setCurrentIndex(row);
   }
}


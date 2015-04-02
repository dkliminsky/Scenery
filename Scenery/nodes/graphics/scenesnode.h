#ifndef SCENESNODE_H
#define SCENESNODE_H

#include "nodes/node.h"
#include "scene.h"
#include "view.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QStackedWidget>
#include <QToolBar>
#include <QTime>


typedef QList<Scene *> Scenes;


class ScenesNode : public QObject, public Node
{ 
    Q_OBJECT
public:
    ScenesNode();
    ~ScenesNode();

    virtual const QString name() { return "Scenes"; }
    virtual const QString tooltip() { return "Scenes"; }
    QWidget *widget() { return _widget; }

    void addScene(Scene *scene);
    void setCurScene(Scene *scene);

protected:
    void timerEvent(QTimerEvent *);

private:
    View _view;
    Scenes _scenes;
    Scene *curScene;

    QMainWindow *_widget;
    QTableWidget *scenesTable;
    QStackedWidget *controlsStacked;
    QAction *fullAct;
    QToolBar *sceneToolBar;
    void createWidget();
    void createActions();
    void createToolBars();

public slots:
    void slotFullScreen(bool isFull);
    void slotChangeScene(int row, int column);

};

#endif // SCENESNODE_H

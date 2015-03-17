#ifndef SCENESNODE_H
#define SCENESNODE_H

#include "nodes/node.h"
#include "scene.h"
#include "view.h"

#include <QTableWidget>
#include <QStackedWidget>


class ScenesNode : public Node, public QObject
{
public:
    ScenesNode();
    ~ScenesNode();

    virtual const QString name() { return "Scenes"; }
    virtual const QString tooltip() { return "Scenes"; }
    QWidget *widget() { return _widget; }

    void addScene(Scene *scene);

protected:
    void timerEvent(QTimerEvent *);

private:
    View _view;
    Scene *_scene;
    QWidget *_widget;
    QTableWidget *scenesTable;
    QStackedWidget *controlsStacked;

    void createWidget();

};

#endif // SCENESNODE_H

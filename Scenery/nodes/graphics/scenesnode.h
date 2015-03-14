#ifndef SCENESNODE_H
#define SCENESNODE_H

#include "nodes/node.h"
#include "scene.h"
#include "view.h"


class ScenesNode : public Node, public QObject
{
public:
    ScenesNode();
    ~ScenesNode();

    virtual const QString name() { return "Scenes"; }
    virtual const QString tooltip() { return "Scenes"; }

    void setScene(Scene *scene);

protected:
    void timerEvent(QTimerEvent *);

private:
    View _view;
    Scene *_scene;

};

#endif // SCENESNODE_H

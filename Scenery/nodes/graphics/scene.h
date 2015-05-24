#ifndef SCENE_H
#define SCENE_H

#include <QString>

#include "nodes/node.h"
#include "tools.h"
#include "graphic.h"
#include "controls/controlprovider.h"


class Scene: public Tools, public Graphic, public ControlProvider
{
public:
    Scene();
    ~Scene();

    virtual QString name() { return "Noname"; }
    virtual void setup(){}
    virtual void resize(){}
    virtual void paint(){}

    Port *input(QString name) { return _inputs->value(name); }

private:
    friend class View;
    friend class ScenesNode;

    Ports *_inputs;
};

#endif // SCENE_H

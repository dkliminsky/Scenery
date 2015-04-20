#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include "control.h"

//#include "nodes/graphics/scene.h"

class Scene;


class ControlButton : public Control
{
public:
    ControlButton(Scene *scene, int id, QString name);
    Scene *scene;
    int id;
};

#endif // CONTROLBUTTON_H

#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include "icontrol.h"

//#include "nodes/graphics/scene.h"

class Scene;


class ControlButton : public IControl
{
public:
    ControlButton(Scene *scene, int id, QString name);
    Scene *scene;
    int id;
};

#endif // CONTROLBUTTON_H

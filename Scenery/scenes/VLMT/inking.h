#ifndef INKING_H
#define INKING_H

#include "graphics/scene.h"

class Inking : public Scene
{
public:
    Inking();

    QString name() { return "Inking"; }

    void setup();
    void paint();


};

#endif // INKING_H

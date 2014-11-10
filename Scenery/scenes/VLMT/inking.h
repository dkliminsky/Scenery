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

private:
    double inkingWingth;
    double inkingLengthLimit;


};

#endif // INKING_H

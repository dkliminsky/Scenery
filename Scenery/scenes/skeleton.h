#ifndef SKELETON_H
#define SKELETON_H

#include "graphics/scene.h"

class Skeleton : public Scene
{
public:
    Skeleton(){}

    QString name() { return "None"; }

    void setup();
    void paint();

private:

};

#endif // SKELETON_H

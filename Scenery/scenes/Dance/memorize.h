#ifndef MEMORIZE_H
#define MEMORIZE_H

#include "graphics/scene.h"

class Memorize : public Scene
{
public:
    Memorize();
    QString name() { return "Memorize"; }

    void paint();

private:
    int stackLength;
    QQueue<Image *> queue;

};

#endif // MEMORIZE_H

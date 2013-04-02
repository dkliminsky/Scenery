#ifndef CAGE_H
#define CAGE_H

#include "graphics/scene.h"

#define MATRIX_SIZE 1000

class Cage : public Scene
{
public:
    Cage();

    QString name() { return "Cage"; }

    void setup();
    void paint();

private:
    Image *box;

    Color backColor;
    Color boxColor;
    int cellSize;
    int boxSize;
    int boxDeviation;
    int influence;
    double prob;

    int cxPrev;
    int cyPrev;
    bool isCenterPrev;

    QVector< QVector<double> > m;

};

#endif // CAGE_H

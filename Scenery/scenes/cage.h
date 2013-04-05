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
    void zeroMatrix(int x1, int y1, int x2, int y2);
    void applyWave();

    Image *box;

    Color backColor;
    Color boxColor;
    int cellSize;
    int boxSize;
    int boxDeviation;
    int influence;
    int prob;
    bool isWave;
    bool isWaveDebug;
    int waveWidth;
    int waveForce;
    int waveSpeed;

    int cxPrev;
    int cyPrev;
    bool isCenterPrev;

    QVector< QVector<double> > m;

    struct Wave {
        float x;
        float y;
        float angle;
        float lenght;
    };
    QList<Wave> waves;

};

#endif // CAGE_H

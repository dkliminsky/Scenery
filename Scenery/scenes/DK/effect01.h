#ifndef EFFECT01_H
#define EFFECT01_H

#include "graphics/scene.h"
#define M_PI_2	3.14159265358979323846/2	/* pi */
#define M_PI_4	3.14159265358979323846/4	/* pi */



/*
 *  Need a SeqAreas
 */

class Effect01 : public Scene
{
public:
    Effect01();

    QString name() { return "Effect 01 Tree"; }

    void setup();
    void paint();

private:
    Color backColor;
    Color treeColor;
    int treeWidth;
    int treeTTL;
    int treeTTLDisappear;
    double treeAlphaDisappear;
    double treeWidhtDisappear;
    int treeGrow;
    int treeGrowLenght;
    int treeGrowDisappear;
    int treeMaxLevel;
    int treeDeviation;

    int treeProbNothing;
    int treeProb0;
    int treeProb45;
    int treeProb90;
    int treeProbTree;

    struct Tree {
        float x;
        float y;
        float angle;
        float lenght;
        float width;
        int level;
        int grow;
        int ttl;
        bool isChildCreate;
        Color color;
    };
    QList<Tree> trees;
    QList<Tree> treesBuf;

};

#endif // EFFECT01_H

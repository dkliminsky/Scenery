#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QDebug>
#include <math.h>

#include "iscene.h"
#include "graphic.h"
#include "control.h"
#include "process/process.h"

class Scene: public IScene, public Graphic, public Control
{
public:
    Scene();

    virtual QString name() = 0;
    virtual void setup() = 0;
    virtual void paint() = 0;

    void setProcessCount(int n);

    void setWidth (int n, int width ) {  widthVector[n] = width;  }
    void setHeight(int n, int height) { heightVector[n] = height; }
    void setAreas(int n, Areas areas) { areasVector[n] = areas; }
    void setSeqAreas(int n, SeqAreas seqAreas) { seqAreasVector[n] = seqAreas; }

    int &getWidth (int n);
    int &getHeight(int n);
    Areas &getAreas(int n);
    SeqAreas &getSeqAreas(int n);

    int time();
    int dtime();

protected:
    void virtual setupEvent(void *view);
    void virtual paintEvent();
    void virtual resizeEvent(int width, int height);

private:
    QVector<int> widthVector;
    QVector<int> heightVector;
    QVector<Areas> areasVector;
    QVector<SeqAreas> seqAreasVector;

    bool firstPaint;

};

#endif // SCENE_H

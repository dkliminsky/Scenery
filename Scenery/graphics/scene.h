#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QDebug>
#include <math.h>

#include "iscene.h"
#include "control.h"
#include "process/process.h"

class Scene: public IScene, public Control
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
    void setContours(int n, Contours contours) { contoursVector[n] = contours; }

    int &getWidth (int n);
    int &getHeight(int n);
    Areas &getAreas(int n);
    SeqAreas &getSeqAreas(int n);
    Contours &getContours(int n);

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
    QVector<Contours> contoursVector;

    bool firstPaint;

};

#endif // SCENE_H

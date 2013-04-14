#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <math.h>

#include "iscene.h"
#include "graphic.h"
#include "process/process.h"

#include "elements/image.h"
#include "elements/color.h"

#include "controls/icontrol.h"
#include "controls/controlint.h"
#include "controls/controldouble.h"
#include "controls/controlbool.h"
#include "controls/controlstring.h"
#include "controls/controlcolor.h"
#include "controls/controlimage.h"
#include "controls/controlbutton.h"


class Scene: public IScene, public Graphic
{
public:
    Scene();

    // Scene API: virtual functions
    virtual QString name() { return "Noname"; }
    virtual void setup(){}
    virtual void paint(){}
    virtual void push(int){}

    // Scene API: data from OpenCV
    int &getWidth (int n);
    int &getHeight(int n);
    Areas &getAreas(int n);
    SeqAreas &getSeqAreas(int n);
    Contours &getContours(int n);

    // Scene API: time
    int time();
    int dtime();

    // Scene API: Control
    void button(int id, QString description);
    void button(int &x, QString description, int min=0, int max=100);
    void button(double &x, QString description, double min=0, double max=100, int precision=1);
    void button(bool &x, QString description);
    void button(QString &string, QString description, QStringList list);
    void button(Color &color, QString description);
    void button(Image **image, QString description, QString path, QString file="");


    void setProcessCount(int n);
    void setWidth (int n, int width ) {  widthVector[n] = width;  }
    void setHeight(int n, int height) { heightVector[n] = height; }
    void setAreas(int n, Areas areas) { areasVector[n] = areas; }
    void setSeqAreas(int n, SeqAreas seqAreas) { seqAreasVector[n] = seqAreas; }
    void setContours(int n, Contours contours) { contoursVector[n] = contours; }

    // Controls
    QWidget     *getWidget() { return widget; }
    QGridLayout *getLayout() { return layout; }
    QVector<IControl *> &getControls() { return controls; }

protected:
    void virtual setupEvent(void *view);
    void virtual paintEvent();
    void virtual resizeEvent(int width, int height);
    void virtual pushButton(int id);

private:
    QVector<int> widthVector;
    QVector<int> heightVector;
    QVector<Areas> areasVector;
    QVector<SeqAreas> seqAreasVector;
    QVector<Contours> contoursVector;

    bool firstPaint;

    // Controls
    QWidget *widget;
    QGridLayout *layout;
    QVector<IControl *> controls;

    void updateControlData();
    void addWidgetValue(QWidget *widget, QString description);
};

#endif // SCENE_H

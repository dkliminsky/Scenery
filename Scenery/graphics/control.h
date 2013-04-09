#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QVector>

#include "graphic.h"

#include "elements/image.h"
#include "elements/color.h"

#include "controls/icontrol.h"
#include "controls/controlint.h"
#include "controls/controldouble.h"
#include "controls/controlbool.h"
#include "controls/controlstring.h"
#include "controls/controlcolor.h"
#include "controls/controlimage.h"

class Control : public Graphic
{
public:
    Control();

    QWidget *getWidget() { return widget; }
    QVector<IControl *> &getControls() { return controls; }

    void control(int &x, QString description, int min=0, int max=100);
    void control(double &x, QString description, double min=0, double max=100, int precision=1);
    void control(bool &x, QString description);
    void control(QString &string, QString description, QStringList list);
    void control(Color &color, QString description);
    void control(Image **image, QString description, QString path, QString file="");

private:
    QWidget *widget;
    QGridLayout *layout;
    QVector<IControl *> controls;

    void addWidget(QWidget *widget, QString description);
};

#endif // CONTROL_H

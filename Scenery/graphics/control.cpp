#include "control.h"

#include <QLayout>
#include <QLabel>
#include <QSlider>
#include <QDebug>

Control::Control()
{
    qDebug() << "Constructor Begin: Control";

    widget = new QWidget();
    layout = new QGridLayout();
    //layout->setContentsMargins(0, 0, 0, 0);
    //layout->setSpacing(0);
    widget->setLayout(layout);

    qDebug() << "Constructor End: Control";
}

void Control::control(int &x, QString description, int min, int max)
{
    ControlInt *data = new ControlInt(x, min, max);
    addWidget(data, description);
}

void Control::control(double &x, QString description, double min, double max, int precision)
{
    ControlDouble *data = new ControlDouble(x, min, max, precision);
    addWidget(data, description);
}

void Control::control(bool &x, QString description)
{
    ControlBool *data = new ControlBool(x);
    addWidget(data, description);
}

void Control::control(QString &string, QString description, QStringList list)
{
    ControlString *data = new ControlString(string, list);
    addWidget(data, description);
}

void Control::control(Color &color, QString description)
{
    ControlColor *data = new ControlColor(color);
    addWidget(data, description);
}

void Control::addWidget(QWidget *widget, QString description)
{
    int row = layout->rowCount();
    layout->addWidget(new QLabel(description), row, 1);
    layout->addWidget(widget, row, 2);
}

#ifndef CONTROLPROVIDER_H
#define CONTROLPROVIDER_H

#include "controls/controls.h"


class ControlProvider
{
public:
    ControlProvider();
    ~ControlProvider();

    virtual void signal(int){}

    void addControl(int &x, QString name, int min=0, int max=999, int step=1);
    void addControl(double &x, QString name, double min=0, double max=100, int precision=1);
    void addControl(bool &x, QString name);
    void addControl(QString &string, QString name, QStringList list);
    void addControl(Color &color, QString name);
    void addControl(Image **image, QString name, QString path, QString file="");
    void addControlGroup(QString name);
    void addButton(int id, QString name);

    Controls &controls() { return _control.controls(); }
    Control &baseControl() { return _control; }

private:
    Control _control;
    Control *curInsertControl;
    Control *lastGroupControl;

    void insertControl(Control *_control);
};

#endif // CONTROLPROVIDER_H

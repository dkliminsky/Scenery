#ifndef ICONTROL_H
#define ICONTROL_H

#include <QString>

class IControl
{
public:
    IControl(QString name) { this->name = name; }

    QString &getName() { return name; }

    virtual void updateData() = 0;
    virtual void setData(QString &data) = 0;
    virtual QString getData() = 0;

protected:
    QString name;

};

#endif // ICONTROL_H

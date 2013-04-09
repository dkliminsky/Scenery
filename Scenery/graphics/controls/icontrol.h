#ifndef ICONTROL_H
#define ICONTROL_H

#include <QString>

class IControl
{
public:
    virtual void setData(QString &data) = 0;
    virtual QString &getData() = 0;
};

#endif // ICONTROL_H

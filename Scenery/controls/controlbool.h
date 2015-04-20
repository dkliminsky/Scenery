#ifndef CONTROLBOOL_H
#define CONTROLBOOL_H

#include "control.h"

class ControlBool : public Control
{
public:
    explicit ControlBool(bool &data, QString name);
    void set(QString &data);
    QString get();

    bool &value() { return _data; }
private:
    bool &_data;

};

#endif // CONTROLBOOL_H

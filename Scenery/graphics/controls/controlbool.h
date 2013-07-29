#ifndef CONTROLBOOL_H
#define CONTROLBOOL_H

#include "icontrol.h"

class ControlBool : public IControl
{
public:
    explicit ControlBool(bool &_data, QString name);
    bool &data() { return _data; }

    void update();
    void set(QString &data);
    QString get();

private:
    bool &_data;

};

#endif // CONTROLBOOL_H

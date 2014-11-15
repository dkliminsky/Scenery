#ifndef CONTROLINT_H
#define CONTROLINT_H

#include "icontrol.h"

class ControlInt : public IControl
{
public:
    explicit ControlInt(int &data, QString name,
                        int min=0, int max=999, int step=1);
    void set(QString &data);
    QString get();

    int &value() { return _data; }
    int min() { return _min; }
    int max() { return _max; }
    int step() { return _step; }

private:
    int &_data;
    int _min;
    int _max;
    int _step;

};

#endif // CONTROLINT_H

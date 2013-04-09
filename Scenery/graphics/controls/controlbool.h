#ifndef CONTROLBOOL_H
#define CONTROLBOOL_H

#include "icontrol.h"

#include <QCheckBox>

class ControlBool : public QCheckBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlBool(bool &data);
    void setData(QString &data);
    QString &getData();

private:
    bool &data;

public slots:
    void slotChange();

};

#endif // CONTROLBOOL_H

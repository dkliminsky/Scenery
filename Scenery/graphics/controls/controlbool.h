#ifndef CONTROLBOOL_H
#define CONTROLBOOL_H

#include <QCheckBox>

#include "icontrol.h"

class ControlBool : public QCheckBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlBool(bool &data, QString name);
    void updateData();
    void setData(QString &data);
    QString getData();

private:
    bool &data;

public slots:
    void slotChange();

};

#endif // CONTROLBOOL_H

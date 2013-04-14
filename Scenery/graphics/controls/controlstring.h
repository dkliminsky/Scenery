#ifndef CONTROLSTRING_H
#define CONTROLSTRING_H

#include "icontrol.h"

#include <QComboBox>
#include <QStringList>

class ControlString : public QComboBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlString(QString &string, QStringList list);
    void updateData(){}
    void setData(QString &data);
    QString &getData() { return *(new QString("")); }

private:
    QString &string;
    
public slots:
    void slotChange();

};

#endif // CONTROLSTRING_H

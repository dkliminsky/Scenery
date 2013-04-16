#ifndef CONTROLSTRING_H
#define CONTROLSTRING_H

#include "icontrol.h"

#include <QComboBox>
#include <QStringList>

class ControlString : public QComboBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlString(QString &string, QString name, QStringList list);
    void updateData();
    void setData(QString &data);
    QString getData();

private:
    QString &string;
    
public slots:
    void slotChange();

};

#endif // CONTROLSTRING_H

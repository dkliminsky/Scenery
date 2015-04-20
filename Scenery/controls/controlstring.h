#ifndef CONTROLSTRING_H
#define CONTROLSTRING_H

#include <QStringList>
#include "control.h"

class ControlString : public Control
{
public:
    ControlString(QString &data, QString name, QStringList list);

    void set(QString &data);
    QString get();

    QString &value() { return _data; }
    QStringList list() { return _list; }

private:
    QString &_data;
    QStringList _list;

};

#endif // CONTROLSTRING_H

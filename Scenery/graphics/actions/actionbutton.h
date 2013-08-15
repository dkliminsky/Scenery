#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QString>

class ActionButton
{
public:
    ActionButton(int id, QString name);

    int id() { return _id; }
    QString &name() { return _name; }

private:
    int _id;
    QString _name;

};

#endif // ACTIONBUTTON_H

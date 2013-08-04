#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(QString name);

    QString &name() { return _name; }

private:
    QString _name;

};

#endif // NODE_H

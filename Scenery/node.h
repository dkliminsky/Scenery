#ifndef NODE_H
#define NODE_H

#include <QThread>

class Node : public QThread
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = 0);
    virtual void step() = 0;

protected:
    virtual void run(){}

signals:
    
public slots:
    
};

#endif // NODE_H

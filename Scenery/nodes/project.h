#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "nodes/node.h"


class Project : public QObject
{
	Q_OBJECT

public:
    explicit Project(QObject *parent = 0);
    ~Project();

    Nodes nodes;
    Nodes sources;

    void saveProject(QString fileName);
    void loadProject(QString fileName);
    virtual void init() {}

protected:
    void timerEvent(QTimerEvent *);

private:
    void writeProject(QJsonObject &json);
    void readProject(QJsonObject &json);
    
};

#endif // PROJECT_H

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

    Nodes sources;
    Nodes nodes;

    void saveProject(QString fileName);
    void loadProject(QString fileName);

protected:
    void timerEvent(QTimerEvent *);
    virtual void init() = 0;

private:
    void writeProject(QJsonObject &json);
    void readProject(QJsonObject &json);
    
};

#endif // PROJECT_H

#include "debug.h"
#include "project.h"
#include "controls/control.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


Project::Project(QObject *parent) :
    QObject(parent)
{
    METHOD_BEGIN

    startTimer(17);

    METHOD_END
}

Project::~Project()
{
    METHOD_BEGIN

    foreach (Node *node, nodes) {
        qDebug() << "Wait Node:" << node->name();
        node->process_wait();
    }

    foreach (Node *node, nodes) {
        qDebug() << "Delete Node:" << node->name();
        delete node;
    }

    METHOD_END
}

void Project::saveProject(QString fileName)
{
    qDebug() << "Save Project:" << fileName;

    QFile saveFile(fileName);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject jsonObject;
    writeProject(jsonObject);
    QJsonDocument saveDoc(jsonObject);
    saveFile.write(saveDoc.toJson());
}

void Project::loadProject(QString fileName)
{
    qDebug() << "Load Project:" << fileName;

    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    readProject(loadDoc.object());
}

void Project::timerEvent(QTimerEvent *)
{
    foreach (Node *node, sources) {
        node->process();
    }
}

void Project::writeProject(QJsonObject &json)
{
    QJsonArray nodesArray;
    foreach(Node *node, nodes) {
        nodesArray.append(node->getJson());
    }
    json["nodes"] = nodesArray;
}

void Project::readProject(QJsonObject &json)
{
    QJsonArray nodesArray = json["nodes"].toArray();
    for(int i=0; i<nodesArray.size(); i++) {
        QJsonObject nodeObject = nodesArray[i].toObject();
        qDebug() << "Read Node:" << nodeObject["name"];
        nodes.at(i)->setJson(nodeObject);
    }
}

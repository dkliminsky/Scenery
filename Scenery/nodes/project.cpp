#include "debug.h"
#include "project.h"
#include "nodes/controls/icontrol.h"

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
        node->process_wait();
        delete node;
    }

    METHOD_END
}

void Project::saveProject(QString fileName)
{
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
       QJsonObject nodeObject;
       nodeObject["uuid"] = node->uuid();
       nodeObject["name"] = node->name();
       nodeObject["posX"] = node->posX();
       nodeObject["posY"] = node->posY();

       QJsonArray controlsArray;
       foreach(IControl *control, node->controls) {
           QJsonObject controlObject;
           controlObject["name"] = control->name();
           controlObject["type"] = control->type();
           controlObject["data"] = control->get();
           controlsArray.append(controlObject);
       }
       nodeObject["controls"] = controlsArray;

       nodesArray.append(nodeObject);
    }
    json["nodes"] = nodesArray;
}

void Project::readProject(QJsonObject &json)
{
    QJsonArray nodesArray = json["nodes"].toArray();
    for(int i=0; i<nodesArray.size(); i++) {
        QJsonObject nodeObject = nodesArray[i].toObject();
        nodes.at(i)->setPos(nodeObject["posX"].toInt(),
                            nodeObject["posY"].toInt());

        QJsonArray controlsArray = nodeObject["controls"].toArray();
        for(int i1=0; i1<controlsArray.size(); i1++) {
            QJsonObject controlObject = controlsArray[i1].toObject();
            nodes.at(i)->controls.at(i1)->set(controlObject["data"].toString());
        }
    }


}

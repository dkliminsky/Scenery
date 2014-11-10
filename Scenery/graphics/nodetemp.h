#ifndef NODE_H
#define NODE_H

#include <QString>
#include "process/processdata.h"

class NodeTemp
{
public:
    NodeTemp(QString name);

    const QString &getName() { return name; }
    bool getIsUpdate() { return isUpdate; }
    void setIsUpdate(bool x) { isUpdate = x; }

    int getWidth() { return width; }
    int getHeight() { return height; }

    IplImage *getImage() { return imageResult; }
    IplImage *getHit() { return hitResult; }

    Areas    &getAreas()    { return areasResult; }
    SeqAreas &getSeqAreas() { return seqAreasResult; }
    Contours &getContours() { return contoursResult; }

    virtual void setCommand(QString) {}

protected:
    QString name;
    bool isUpdate;

    int width;
    int height;

    Areas    areasResult;
    SeqAreas seqAreasResult;
    Contours contoursResult;

    IplImage *imageResult;
    IplImage *hitResult;
};

#endif // NODE_H

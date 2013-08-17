#ifndef NODE_H
#define NODE_H

#include <QString>
#include "process/processdata.h"

class Node
{
public:
    Node(QString name);

    const QString &getName() { return name; }

    int getWidth() { return width; }
    int getHeight() { return height; }

    IplImage *getImage() { return imageResult; }
    IplImage *getHit() { return hitResult; }

    Areas    &getAreas()    { return areasResult; }
    SeqAreas &getSeqAreas() { return seqAreasResult; }
    Contours &getContours() { return contoursResult; }

protected:
    QString name;

    int width;
    int height;

    Areas    areasResult;
    SeqAreas seqAreasResult;
    Contours contoursResult;

    IplImage *imageResult;
    IplImage *hitResult;
};

#endif // NODE_H

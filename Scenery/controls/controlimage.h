#ifndef CONTROLIMAGE_H
#define CONTROLIMAGE_H

#include "control.h"
#include "nodes/graphics/elements/image.h"

class ControlImage : public Control
{
public:
    ControlImage(Image **image, QString name,
                 QVector<Image*> images);

    void set(QString &data);
    QString get();

    Image **value() { return _image; }
    QVector<Image*> images() { return _images; }

private:
    Image **_image;
    QVector<Image*> _images;

};

#endif // CONTROLIMAGE_H

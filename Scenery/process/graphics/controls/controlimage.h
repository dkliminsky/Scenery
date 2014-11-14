#ifndef CONTROLIMAGE_H
#define CONTROLIMAGE_H

#include "icontrol.h"
#include "../elements/image.h"

class ControlImage : public IControl
{
public:
    ControlImage(Image **img, QString name,
                 QVector<Image*> images);

    void set(QString &data);
    QString get();

    Image **value() { return _img; }
    QVector<Image*> images() { return _images; }

private:
    Image **_img;
    QVector<Image*> _images;

};

#endif // CONTROLIMAGE_H

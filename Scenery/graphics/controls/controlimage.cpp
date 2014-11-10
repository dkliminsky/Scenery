#include "controlimage.h"
#include <QDebug>

ControlImage::ControlImage(Image **img, QString name,
                           QVector<Image *> images):
    IControl(IControl::ControlImage, name), _img(img)
{
    _images = images;
}

void ControlImage::set(QString &data)
{
    for (int i=0; i<_images.size(); i++) {
        if (_images.at(i)->fileName() == data) {
            (*_img) = _images[i];
            break;
        }
    }
}

QString ControlImage::get()
{
    return (*_img)->fileName();
}

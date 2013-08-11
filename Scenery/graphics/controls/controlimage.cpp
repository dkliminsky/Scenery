#include "controlimage.h"

ControlImage::ControlImage(Image **img, QString name,
                           QVector<Image *> images):
    IControl(IControl::ControlImage, name), _img(img)
{
    _images = images;
}

void ControlImage::set(QString &data)
{

}

QString ControlImage::get()
{
    return (*_img)->name();
}

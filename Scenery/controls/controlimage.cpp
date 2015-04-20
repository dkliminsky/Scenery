#include "controlimage.h"

ControlImage::ControlImage(Image **image, QString name,
                           QVector<Image *> images):
    Control(Control::ControlImage, name), _image(image)
{
    _images = images;
}

void ControlImage::set(QString &data)
{
    for (int i=0; i<_images.size(); i++) {
        if (_images.at(i)->fileName() == data) {
            (*_image) = _images[i];
            break;
        }
    }
}

QString ControlImage::get()
{
    return (*_image)->fileName();
}

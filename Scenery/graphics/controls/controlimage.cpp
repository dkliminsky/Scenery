#include "controlimage.h"

ControlImage::ControlImage(Image **image, QString name, QVector<Image *> images, int index) :
    IControl(name)
{
    Q_ASSERT(index <= images.size());

    this->image = image;
    this->images = images;
    QStringList list;
    for (int i = 0; i < images.size(); i++) {
        list << images.at(i)->getFileName();
    }

    this->addItems(list);
    this->setCurrentIndex(index);

    connect(this, SIGNAL(currentIndexChanged(int)), SLOT(slotChange()));
}

void ControlImage::updateData()
{
    // ...
}

void ControlImage::setData(QString &data)
{
    int i = this->findText(data);
    if (i >= 0) {
        this->setCurrentIndex(i);
    }
}

QString ControlImage::getData()
{
    return (*image)->getFileName();
}

void ControlImage::slotChange()
{
    *image = images.at(this->currentIndex());
}

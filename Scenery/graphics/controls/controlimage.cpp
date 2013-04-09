#include "controlimage.h"

ControlImage::ControlImage(Image **image, QVector<Image *> images, int index)
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

    connect(this, SIGNAL(activated(int)), SLOT(slotChange()));
}

void ControlImage::slotChange()
{
    *image = images.at(this->currentIndex());
}

#ifndef CONTROLIMAGE_H
#define CONTROLIMAGE_H

#include <QComboBox>
#include <QStringList>

#include "../elements/image.h"

class ControlImage : public QComboBox
{
    Q_OBJECT
public:
    explicit ControlImage(Image **image, QVector<Image*> images, int index);

public slots:
    void slotChange();

private:
    Image **image;
    QVector<Image*> images;
};

#endif // CONTROLIMAGE_H

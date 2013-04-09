#ifndef CONTROLIMAGE_H
#define CONTROLIMAGE_H

#include "icontrol.h"
#include "../elements/image.h"

#include <QComboBox>
#include <QStringList>

class ControlImage : public QComboBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlImage(Image **image, QVector<Image*> images, int index);
    void setData(QString &data) { ; }
    QString &getData() { return *(new QString("")); }


public slots:
    void slotChange();

private:
    Image **image;
    QVector<Image*> images;
};

#endif // CONTROLIMAGE_H

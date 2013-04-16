#ifndef CONTROLIMAGE_H
#define CONTROLIMAGE_H

#include <QComboBox>
#include <QStringList>

#include "icontrol.h"
#include "../elements/image.h"

class ControlImage : public QComboBox, public IControl
{
    Q_OBJECT
public:
    explicit ControlImage(Image **image, QString name, QVector<Image*> images, int index);
    void updateData();
    void setData(QString &data);
    QString getData();

public slots:
    void slotChange();

private:
    Image **image;
    QVector<Image*> images;
};

#endif // CONTROLIMAGE_H

#ifndef CONTROLIMAGEWIDGET_H
#define CONTROLIMAGEWIDGET_H

#include <QComboBox>
#include <QStringList>
#include "icontrolwidget.h"
#include "graphics/controls/controlimage.h"


class ControlImageWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlImageWidget(ControlImage *control);
    void update();

private:
    ControlImage *control;
    QComboBox *comboBox;
    QString curFileName();

signals:

private slots:
    void slotChange();

};

#endif // CONTROLIMAGEWIDGET_H

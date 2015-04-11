#ifndef CONTROLIMAGEWIDGET_H
#define CONTROLIMAGEWIDGET_H

#include <QComboBox>
#include <QStringList>
#include "nodes/controls/controlimage.h"


class ControlImageWidget : public QComboBox
{
    Q_OBJECT
public:
    ControlImageWidget(ControlImage *control, QWidget *parent = 0);

private:
    ControlImage *control;

public slots:
    void change();
    void update();
};

#endif // CONTROLIMAGEWIDGET_H

#ifndef CONTROLBUTTONWIDGET_H
#define CONTROLBUTTONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "controls/controlbutton.h"
#include "nodes/graphics/scene.h"

class ControlButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlButtonWidget(ControlButton *control, QWidget *parent = 0);

private:
    Scene *scene;
    ControlButton *control;

signals:

public slots:
    void button();
};

#endif // CONTROLBUTTONWIDGET_H

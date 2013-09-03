#ifndef CONTROLBUTTONWIDGET_H
#define CONTROLBUTTONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "graphics/controls/controlbutton.h"
#include "graphics/scene.h"

class ControlButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlButtonWidget(Scene *scene, ControlButton *control, QWidget *parent = 0);

private:
    Scene *scene;
    ControlButton *control;
    QVector<ControlButton::Button> buttons;

signals:

public slots:
    void button0();
    void button1();
    void button2();
    void button3();

};

#endif // CONTROLBUTTONWIDGET_H

#ifndef CONTROLBUTTONWIDGET_H
#define CONTROLBUTTONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "icontrolwidget.h"
#include "graphics/controls/controlbutton.h"
#include "graphics/scene.h"

class ControlButtonWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlButtonWidget(Scene *scene, ControlButton *control);

private:
    Scene *scene;
    ControlButton *control;
    QVector<ControlButton::Button> buttons;

signals:

private slots:
    void button0();
    void button1();
    void button2();
    void button3();
    void button4();
    void button5();

};

#endif // CONTROLBUTTONWIDGET_H

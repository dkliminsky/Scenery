#ifndef CONTROLINTWIDGET_H
#define CONTROLINTWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include "graphics/controls/controlint.h"

class ControlIntWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlIntWidget(ControlInt *control, QWidget *parent = 0);
    
private:
    ControlInt *control;
    QSlider *slider;
    QLabel *label;
    QHBoxLayout *hLayout;


signals:
    
public slots:
    void change();
    void update();

};

#endif // CONTROLINTWIDGET_H

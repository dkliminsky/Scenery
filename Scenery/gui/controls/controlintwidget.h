#ifndef CONTROLINTWIDGET_H
#define CONTROLINTWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include "icontrolwidget.h"
#include "graphics/controls/controlint.h"

class ControlIntWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlIntWidget(ControlInt *control);
    void update();

private:
    ControlInt *control;
    QSlider *slider;
    QLabel *label;
    QHBoxLayout *hLayout;

signals:
    
private slots:
    void slotChange();

};

#endif // CONTROLINTWIDGET_H

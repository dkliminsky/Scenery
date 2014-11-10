#ifndef CONTROLCOLORWIDGET_H
#define CONTROLCOLORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QColorDialog>
#include "icontrolwidget.h"
#include "graphics/controls/controlcolor.h"

class ControlColorWidget : public IControlWidget
{
    Q_OBJECT
public:
    explicit ControlColorWidget(ControlColor *control);
    void update();

private:
    ControlColor *control;
    QHBoxLayout *hLayout;
    QDoubleSpinBox *spinR;
    QDoubleSpinBox *spinG;
    QDoubleSpinBox *spinB;
    QDoubleSpinBox *spinA;
    QPushButton *button;
    QColorDialog *colorDialog;
    bool isSlotChangeOn;

signals:
    
private slots:
    void slotChange();
    void showColorDialog();
    void changeColor(QColor c);
};

#endif // CONTROLCOLORWIDGET_H

#ifndef CONTROLCOLORWIDGET_H
#define CONTROLCOLORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QColorDialog>
#include "nodes/controls/controlcolor.h"

class ControlColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlColorWidget(ControlColor *control,
                                QWidget *parent = 0);
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
    
public slots:
    void change();
    void update();

    void showColorDialog();
    void changeColor(QColor c);
};

#endif // CONTROLCOLORWIDGET_H

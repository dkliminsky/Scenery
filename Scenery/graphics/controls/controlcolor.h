#ifndef CONTROLCOLOR_H
#define CONTROLCOLOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QColorDialog>

#include "icontrol.h"
#include "../elements/color.h"

class ControlColor : public QWidget, public IControl
{
    Q_OBJECT
public:
    explicit ControlColor(Color &color, QString name);
    void updateData();
    void setData(QString &data);
    QString getData();

private:
    bool isSlotOn;
    Color &color;
    QHBoxLayout *hLayout;
    QDoubleSpinBox *spinR;
    QDoubleSpinBox *spinG;
    QDoubleSpinBox *spinB;
    QDoubleSpinBox *spinA;
    QPushButton *button;
    QColorDialog *colorDialog;

public slots:
    void slotChange();
    void slotColorDialog();
    void slotColorDialogSelected(QColor c);
};

#endif // CONTROLCOLOR_H

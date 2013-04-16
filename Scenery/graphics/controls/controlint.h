#ifndef CONTROLINT_H
#define CONTROLINT_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

#include "icontrol.h"

class ControlInt : public QWidget, public IControl
{
    Q_OBJECT
public:
    explicit ControlInt(int &data, QString name, int min, int max);
    void updateData();
    void setData(QString &data);
    QString getData();

private:
    int &data;
    QSlider *slider;
    QLabel *label;
    QHBoxLayout *hLayout;
    
public slots:
    void slotChange();

};

#endif // CONTROLINT_H

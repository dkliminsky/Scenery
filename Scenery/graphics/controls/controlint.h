#ifndef CONTROLINT_H
#define CONTROLINT_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

class ControlInt : public QWidget
{
    Q_OBJECT
public:
    explicit ControlInt(int &data, int min, int max);

private:
    int &data;
    QSlider *slider;
    QLabel *label;
    QHBoxLayout *hLayout;
    
public slots:
    void slotChange();

};

#endif // CONTROLINT_H

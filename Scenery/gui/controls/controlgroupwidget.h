#ifndef CONTROLGROUPWIDGET_H
#define CONTROLGROUPWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include "nodes/controls/controlgroup.h"


class ControlGroupWidget : public QGroupBox
{
public:
    ControlGroupWidget(ControlGroup *control);
    ~ControlGroupWidget();

    void addControlWidget(QWidget *widget);

private:
    QHBoxLayout *layout;

};

#endif // CONTROLGROUPWIDGET_H

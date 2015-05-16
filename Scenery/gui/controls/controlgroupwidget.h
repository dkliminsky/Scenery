#ifndef CONTROLGROUPWIDGET_H
#define CONTROLGROUPWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include "controls/controlgroup.h"


class ControlGroupWidget : public QGroupBox
{
public:
    ControlGroupWidget(ControlGroup *control);
    ~ControlGroupWidget();

};

#endif // CONTROLGROUPWIDGET_H

#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include "control.h"

class ControlProvider;


class ControlButton : public Control
{
public:
    ControlButton(ControlProvider *provider, int id, QString name);
    ControlProvider *provider;
    int id;
};

#endif // CONTROLBUTTON_H

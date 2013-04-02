#include "controlbool.h"

ControlBool::ControlBool(bool &data) :
    data(data)
{
    this->setChecked(data);
    connect(this, SIGNAL(clicked()), SLOT(slotChange()));
}

void ControlBool::slotChange()
{
    data = this->isChecked();
}

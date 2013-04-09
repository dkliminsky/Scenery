#include "controlbool.h"

ControlBool::ControlBool(bool &data) :
    data(data)
{
    this->setChecked(data);
    connect(this, SIGNAL(clicked()), SLOT(slotChange()));
}

void ControlBool::setData(QString &data)
{
    if (data.toLower() == "true")
        this->data = true;
    else
        this->data = false;
}

QString &ControlBool::getData()
{


    if (data)
        return *(new QString("true"));
    else
        return *(new QString("false"));
}

void ControlBool::slotChange()
{
    data = this->isChecked();
}

#include "controlbool.h"

ControlBool::ControlBool(bool &data, QString name) :
    IControl(name), data(data)
{
    connect(this, SIGNAL(clicked()), SLOT(slotChange()));
    updateData();
}

void ControlBool::updateData()
{
    this->setChecked(data);
}

void ControlBool::setData(QString &data)
{
    if (data.toLower() == "true")
        this->data = true;
    else
        this->data = false;

    updateData();
}

QString ControlBool::getData()
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

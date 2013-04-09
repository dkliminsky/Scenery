#include "controlstring.h"

ControlString::ControlString(QString &string, QStringList list) :
    string(string)
{
    if (list.contains(string))
        this->addItems(list);
    else {
        this->addItem(string);
        this->addItems(list);
    }

    connect(this, SIGNAL(activated(int)), SLOT(slotChange()));
}

void ControlString::setData(QString &data)
{
}

void ControlString::slotChange()
{
    string = this->currentText();
}

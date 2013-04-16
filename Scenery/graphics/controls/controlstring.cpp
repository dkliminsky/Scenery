#include "controlstring.h"

ControlString::ControlString(QString &string, QString name, QStringList list) :
    IControl(name), string(string)
{
    if (list.contains(string))
        this->addItems(list);
    else {
        this->addItem(string);
        this->addItems(list);
    }

    connect(this, SIGNAL(currentIndexChanged(int)), SLOT(slotChange()));
}

void ControlString::updateData()
{
    int i = this->findText(string);
    if (i >= 0)
        this->setCurrentIndex(i);
}

void ControlString::setData(QString &data)
{
    int i = this->findText(data);
    if (i >= 0)
        this->setCurrentIndex(i);
}

QString ControlString::getData()
{
    return string;
}

void ControlString::slotChange()
{
    string = this->currentText();
}

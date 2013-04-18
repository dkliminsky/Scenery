#include "tablebutton.h"

TableButton::TableButton(int row, QWidget *parent) :
    QPushButton(parent)
{
    this->row = row;
    this->setIcon(QIcon(":/icons/icons/play.png"));
    connect(this, SIGNAL(clicked()), SLOT(slotClicked()));
}


void TableButton::slotClicked()
{
    emit signalClicked(row);
}

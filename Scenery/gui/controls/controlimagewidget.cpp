#include "controlimagewidget.h"

ControlImageWidget::ControlImageWidget(ControlImage *control, QWidget *parent) :
    QComboBox(parent),
    control(control)
{
    QStringList list;
    for (int i=0; i<control->images().size(); i++) {
        list += control->images().at(i)->fileName();
    }
    addItems(list);

    update();
    connect(this, SIGNAL(currentIndexChanged(int)), SLOT(change()));
}

void ControlImageWidget::change()
{
    QString s = currentText();
    control->set(s);
}

void ControlImageWidget::update()
{
    int i = findText(control->get());
    if (i >= 0) {
        setCurrentIndex(i);
    }
}


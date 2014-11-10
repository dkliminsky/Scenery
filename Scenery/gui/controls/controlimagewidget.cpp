#include "controlimagewidget.h"
#include <QHBoxLayout>

ControlImageWidget::ControlImageWidget(ControlImage *control)
{
    this->control = control;

    comboBox = new QComboBox();

    QStringList list;
    for (int i=0; i<control->images().size(); i++) {
        list += control->images().at(i)->fileName();
    }
    comboBox->addItems(list);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(comboBox);
    this->setLayout(layout);

    update();
    connect(comboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotChange()));
}

void ControlImageWidget::slotChange()
{
    QString s = comboBox->currentText();
    control->set(s);
}

void ControlImageWidget::update()
{
    int i = comboBox->findText(control->get());
    if (i >= 0) {
        comboBox->setCurrentIndex(i);
    }
}


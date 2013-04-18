#ifndef TABLEBUTTON_H
#define TABLEBUTTON_H

#include <QPushButton>

class TableButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TableButton(int row, QWidget *parent = 0);
    
private:
    int row;

signals:
    void signalClicked(int row);

public slots:
    void slotClicked();
    
};

#endif // TABLEBUTTON_H

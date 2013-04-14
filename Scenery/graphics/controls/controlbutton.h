#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include <QPushButton>

#include "../iscene.h"

class ControlButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ControlButton(IScene *scene, int id, QString text);

private:
    int id;
    IScene *scene;
    
public slots:
    void slotPush();
    
};

#endif // CONTROLBUTTON_H

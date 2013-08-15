#ifndef ACTIONBUTTONWIDGET_H
#define ACTIONBUTTONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "graphics/scene.h"

class ActionButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionButtonWidget(Scene *scene, int id, QWidget *parent = 0);
    
private:
    Scene *scene;
    int id;

    QPushButton *pushButton;
    QHBoxLayout *hLayout;

signals:
    
public slots:
    void signal();
    
};

#endif // ACTIONBUTTONWIDGET_H

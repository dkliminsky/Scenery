#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manager.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Manager *manager, QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);

private:
    Ui::MainWindow *ui;
    Manager *manager;

public slots:
    void changeScene(int n);

};

#endif // MAINWINDOW_H

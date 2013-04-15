#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Manager *manager, QWidget *parent = 0);
    ~MainWindow();

    void saveControls(Scene *scene, QString file, int state=0);
    void loadControls(Scene *scene, QString file, int state=0);
    void loadControlsStates(QString file);

protected:
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);

private:
    Ui::MainWindow *ui;
    Manager *manager;

public slots:
    void changeScene(int n);
    void setFullScreen(bool full);
    void slotProcessParam();

};

#endif // MAINWINDOW_H

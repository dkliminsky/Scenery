#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "manager.h"
#include "processwindow.h"
#include "processdebug.h"

typedef QVector<ProcessWindow *> ProcessWindows;

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
    ProcessWindows processWindows;

public slots:
    void slotEditProcess(int row, int colomn);
    void slotChangeScene(int row, int colomn);

};

#endif // MAINWINDOW_H

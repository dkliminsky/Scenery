#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "manager.h"
#include "processwindow.h"

#include "controls/controlboolwidget.h"
#include "controls/controlintwidget.h"
#include "controls/controldoublewidget.h"
#include "controls/controlstringwidget.h"
#include "controls/controlcolorwidget.h"
#include "controls/controlbuttonwidget.h"

typedef QVector<ProcessWindow *> ProcessWindows;
typedef QVector<QWidget *> ControlWidgets;

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
    ControlWidgets controlWidgets;
    int curScene;

public slots:
    void setFullScreen(bool full);

    void slotEditProcess(int row, int colomn);
    void slotChangeScene(int row, int colomn);

};

#endif // MAINWINDOW_H

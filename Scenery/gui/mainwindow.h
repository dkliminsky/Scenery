#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "manager.h"
#include "processwindow.h"

#include "controls/icontrolwidget.h"
#include "controls/controlboolwidget.h"
#include "controls/controlintwidget.h"
#include "controls/controldoublewidget.h"
#include "controls/controlstringwidget.h"
#include "controls/controlcolorwidget.h"
#include "controls/controlbuttonwidget.h"

typedef QVector<ProcessWindow *> ProcessWindows;
typedef QVector<IControlWidget *> ControlWidgets;
typedef QVector<ControlWidgets> ControlWidgetsScenes;

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
    ControlWidgetsScenes controlWidgetsScenes;
    int curScene;

    void loadControls(int numScene);

public slots:
    void setFullScreen(bool full);

    void slotEditProcess(int row, int colomn);
    void slotChangeScene(int row, int colomn);

    void slotSaveControls();
    void slotLoadControls();

};

#endif // MAINWINDOW_H

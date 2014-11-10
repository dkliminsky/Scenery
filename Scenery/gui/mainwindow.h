#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "manager.h"
#include "nodeitem.h"

#include "controls/controlboolwidget.h"
#include "controls/controlintwidget.h"
#include "controls/controldoublewidget.h"
#include "controls/controlstringwidget.h"
#include "controls/controlcolorwidget.h"
#include "controls/controlbuttonwidget.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QGraphicsView;
class QGraphicsScene;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Manager *manager, QWidget *parent = 0);
    ~MainWindow();

    void addNode(Node *node);

protected:
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);

private:
    Manager *manager;
    QGraphicsScene *scene;
    QGraphicsView *graphics;

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QMenu *fileMenu;
    QMenu *helpMenu;

    void readSettings();
    void createActions();
    void createMenus();
    void createScene();

private slots:
    void about();

public slots:
    void setFullScreen(bool full);

};

#endif // MAINWINDOW_H

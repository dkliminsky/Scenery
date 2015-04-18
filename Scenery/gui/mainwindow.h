#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../nodes/project.h"
#include "nodeitem.h"
#include "linkitem.h"

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
    explicit MainWindow(Project *manager, QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);

    NodeItem *getOrCreateNodeItem(Node *node);

private:
    Project *manager;
    QGraphicsScene *scene;
    QGraphicsView *graphics;

    QHash<QString, NodeItem *> nodeItemHash;

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *saveAct;
    QAction *loadAct;
    QMenu *fileMenu;
    QMenu *helpMenu;

    QToolBar *mainToolBar;

    void readSettings();

    void createActions();
    void createToolBars();
    void createMenus();
    void createScene();
    void createNodes();

private slots:
    void slotAbout();
    void slotSave();
    void slotLoad();

};

#endif // MAINWINDOW_H

#include <QtWidgets>

#include "mainwindow.h"
#include "process/node.h"
#include "debug.h"


MainWindow::MainWindow(Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    manager(manager)
{
    METHOD_BEGIN

    createActions();
    createMenus();
    createScene();
    readSettings();

    foreach (Node *node, manager->sources) {
        addNode(node);
    }

    startTimer(500);

    METHOD_END
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.endGroup();
    qApp->exit(0);
}

void MainWindow::timerEvent(QTimerEvent *)
{

}

void MainWindow::setFullScreen(bool full)
{

}

void MainWindow::readSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    restoreState(settings.value("MainWindow/windowState").toByteArray());
}

void MainWindow::createActions() {
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the Scenery About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createScene()
{
    scene = new QGraphicsScene();
    graphics = new QGraphicsView(scene);
    setCentralWidget(graphics);
}

void MainWindow::addNode(Node *node)
{
    NodeItem *nodeItem = new NodeItem(node);
    scene->addItem(nodeItem);

    foreach (Port *port, node->out) {
        foreach (Link *link, port->links) {
            Node *next = link->node;
            addNode(next);
        }
    }
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Scenery"),
            tr("The <b>Scenery</b> project."));
}

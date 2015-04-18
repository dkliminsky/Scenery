#include <QtWidgets>

#include "mainwindow.h"
#include "nodes/node.h"
#include "debug.h"


MainWindow::MainWindow(Project *manager, QWidget *parent) :
    QMainWindow(parent),
    manager(manager)
{
    METHOD_BEGIN

    createActions();
    createToolBars();
    createMenus();
    createScene();
    readSettings();

    manager->loadProject("config.json");
    createNodes();

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

NodeItem *MainWindow::getOrCreateNodeItem(Node *node)
{
    if (nodeItemHash.contains(node->uuid())) {
        return nodeItemHash.value(node->uuid());
    }

    NodeItem *nodeItem = new NodeItem(node);
    nodeItemHash.insert(node->uuid(), nodeItem);
    scene->addItem(nodeItem);
    return nodeItem;
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
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(slotAbout()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    saveAct = new QAction(QIcon(":/icons/resources/icons/save.svg"),
                          tr("&Save"), this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(slotSave()));

    loadAct = new QAction(QIcon(":/icons/resources/icons/load.svg"),
                          tr("&Load"), this);
    connect(loadAct, SIGNAL(triggered()), this, SLOT(slotLoad()));
}

void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("Main"));
    mainToolBar->addAction(saveAct);
    mainToolBar->addAction(loadAct);
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

void MainWindow::createNodes()
{
    foreach (Node *node, manager->nodes) {
        NodeItem *nodeItem = getOrCreateNodeItem(node);

        foreach (Port *port, node->outputs) {
            foreach (Link *link, port->links) {
                Node *next = link->node;
                LinkItem *linkItem = new LinkItem(node, next);
                scene->addItem(linkItem);
                nodeItem->links_out.append(linkItem);

                NodeItem *nextItem = getOrCreateNodeItem(next);
                nextItem->links_in.append(linkItem);
            }
        }
    }
}

void MainWindow::slotAbout()
{
   QMessageBox::about(this, tr("About Scenery"),
                      tr("The <b>Scenery</b> project."));
}

void MainWindow::slotSave()
{
    manager->saveProject("config.json");
}

void MainWindow::slotLoad()
{
    manager->loadProject("config.json");
    scene->update();
}

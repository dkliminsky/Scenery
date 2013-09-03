#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "Constructor Begin: MainWindow";

    ui->setupUi(this);
    this->manager = manager;
    curScene = 0;

    Inputs &inputs = manager->getInputs();
    Processes &processes = manager->getProcesses();
    Scenes &scenes = manager->getScenes();

    ui->tableInputs->setRowCount(inputs.size());
    for (int i=0; i<inputs.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(tr("Camera %1").arg(i+1));
        ui->tableInputs->setItem(i, 0, item);
    }
    ui->tableInputs->resizeColumnsToContents();

    ui->tableProcesses->setRowCount(processes.size());
    for (int i=0; i<processes.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(processes.at(i)->getName());
        ui->tableProcesses->setItem(i, 0, item);
        processWindows += new ProcessWindow(processes.at(i), manager->name() + ".ini");
    }
    ui->tableProcesses->resizeColumnsToContents();
    connect(ui->tableProcesses, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::slotEditProcess);

    ui->tableScenes->setRowCount(scenes.size());
    for (int i=0; i<scenes.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(scenes.at(i)->name());
        ui->tableScenes->setItem(i, 0, item);
        ui->tableScenes->setItem(i, 1, new QTableWidgetItem("0"));
    }
    ui->tableScenes->resizeColumnsToContents();
    connect(ui->tableScenes, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::slotChangeScene);

    for(int i=0; i<scenes.size(); i++) {
        Scene *scene = scenes.at(i);

        QWidget *widget = new QWidget();
        QGridLayout *layout = new QGridLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        //layout->setSpacing(3);

        int n = 0;

        for (int j=0; j<scene->actions().size(); j++) {
            ActionButton *action = scene->actions().at(j);
            layout->addWidget(new QLabel(action->name()), n, 0);
            layout->addWidget(new ActionButtonWidget(scenes.at(i), action->id()), n, 1);
            n++;
        }

        for (int j=0; j<scene->controls().size(); j++) {
            IControl *control = scene->controls().at(j);
            layout->addWidget(new QLabel(control->name()), n, 0);
            switch(control->type()) {
            case IControl::ControlBool:
                layout->addWidget(new ControlBoolWidget(static_cast<ControlBool *>(control)), n, 1);
                break;
            case IControl::ControlInt:
                layout->addWidget(new ControlIntWidget(static_cast<ControlInt *>(control)), n, 1);
                break;
            case IControl::ControlDouble:
                layout->addWidget(new ControlDoubleWidget(static_cast<ControlDouble *>(control)), n, 1);
                break;
            case IControl::ControlString:
                layout->addWidget(new ControlStringWidget(static_cast<ControlString *>(control)), n, 1);
                break;
            case IControl::ControlColor:
                layout->addWidget(new ControlColorWidget(static_cast<ControlColor *>(control)), n, 1);
                break;
            case IControl::ControlImage:
                break;
            case IControl::ControlButton:
                layout->addWidget(new ControlButtonWidget(scenes.at(i),
                                  static_cast<ControlButton *>(control)));
            }
            n++;
        }

        if (layout->count() > 0)
            layout->setRowStretch(layout->count()-1, 1);

        widget->setLayout(layout);
        ui->controlsStackedWidget->addWidget(widget);
    }

//        if (scene->getLayout()->count() > 0)
//            scene->getLayout()->setRowStretch(scene->getLayout()->count()-1, 1);

    connect(ui->actionFullScreen, SIGNAL(toggled(bool)), SLOT(setFullScreen(bool)));

    startTimer(500);

    qDebug() << "Constructor End: MainWindow";
}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i=0; i<processWindows.size(); i++) {
        delete processWindows[i];
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    qApp->exit(0);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    ui->tableScenes->setItem(curScene, 1,
                             new QTableWidgetItem(QString().number(manager->getViews().at(0)->fps())));

    for(int i=0; i<manager->getInputs().size(); i++) {
        ui->tableInputs->setItem(i, 1,
                                 new QTableWidgetItem(QString().number(manager->getInputs().at(i)->getTime())));
    }

    for(int i=0; i<manager->getProcesses().size(); i++) {
        ui->tableProcesses->setItem(i, 1,
                                 new QTableWidgetItem(QString().number(manager->getProcesses().at(i)->getTime())));
    }

}

void MainWindow::setFullScreen(bool full)
{
    if (full)
        manager->getViews().at(0)->showFullScreen();
    else
        manager->getViews().at(0)->showNormal();
}

void MainWindow::slotEditProcess(int row, int column)
{
    if ( column == 0) {
        processWindows.at(row)->show();
    }
    else if (column == 2) {
        for(int i=0; i<manager->getProcesses().size(); i++) {
            manager->getProcesses().at(i)->setDebug(false);
            ui->tableProcesses->setItem(i, 2, new QTableWidgetItem(""));
        }
        manager->getProcesses().at(row)->setDebug(true);
        ui->tableProcesses->setItem(row, 2, new QTableWidgetItem("x"));
    }
}

void MainWindow::slotChangeScene(int row, int column)
{
    if ( column == 0) {
        manager->getViews().at(0)->setScene(manager->getScenes().at(row));
        curScene = row;
        ui->controlsStackedWidget->setCurrentIndex(row);
    }
}

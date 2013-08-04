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

    ui->tableInputs->setRowCount(manager->getInputs().size());
    for (int i=0; i<manager->getInputs().size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(tr("Camera %1").arg(i+1));
        ui->tableInputs->setItem(i, 0, item);
    }

    ui->tableProcesses->setRowCount(manager->getProcesses().size());
    for (int i=0; i<manager->getProcesses().size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(tr("Process %1").arg(i+1));
        ui->tableProcesses->setItem(i, 0, item);
        processWindows += new ProcessWindow(manager->getProcesses().at(i), QString("process_%1.ini").arg(i+1));
    }
    connect(ui->tableProcesses, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::slotEditProcess);

    ui->tableScenes->setRowCount(manager->getScenes().size());
    for (int i=0; i<manager->getScenes().size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(manager->getScenes().at(i)->name());
        ui->tableScenes->setItem(i, 0, item);
    }
    connect(ui->tableScenes, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::slotChangeScene);

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

}

void MainWindow::slotEditProcess(int row, int)
{
    processWindows.at(row)->show();
}

void MainWindow::slotChangeScene(int row, int)
{
    manager->getViews().at(0)->setScene(manager->getScenes().at(row));
}

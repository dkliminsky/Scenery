#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(Manager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->manager = manager;

    for(int i=0; i<manager->getScenes().size(); i++) {
        ui->scenesComboBox->addItem(manager->getScenes().at(i)->name());
        ui->scenesStackedWidget->addWidget(manager->getScenes().at(i)->getWidget());
    }
    connect(ui->scenesComboBox, SIGNAL(activated(int)), SLOT(changeScene(int)));

    connect(ui->actionFullScreen, SIGNAL(toggled(bool)), SLOT(setFullScreen()));

    manager->setScene(0);
    ui->scenesComboBox->setCurrentIndex(0);
    ui->scenesStackedWidget->setCurrentIndex(0);

    startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    qApp->exit(0);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    ui->graphicFPSLabel->setNum(manager->getView()->getFPS());
    ui->input1FPSLabel->setNum(manager->getInputs().at(0)->getFPS());
}

void MainWindow::changeScene(int n)
{
    manager->setScene(n);
    ui->scenesStackedWidget->setCurrentIndex(n);
}

void MainWindow::setFullScreen()
{
    manager->getView()->showFullScreen();
}

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

    for(int i=0; i<manager->getScenes().size(); i++) {
        Scene *scene = manager->getScenes().at(i);
        ui->scenesComboBox->addItem(scene->name());
        if (scene->getLayout()->count() > 0)
            scene->getLayout()->setRowStretch(scene->getLayout()->count()-1, 1);
        ui->scenesStackedWidget->addWidget(scene->getWidget());
        loadControls(scene, "controls.ini", 0);
    }

    processWindow = new ProcessWindow(manager->getProcesses().at(0), "process.ini");

    connect(ui->scenesComboBox, SIGNAL(activated(int)), SLOT(changeScene(int)));
    connect(ui->actionFullScreen, SIGNAL(toggled(bool)), SLOT(setFullScreen(bool)));
    connect(ui->processParamButton, SIGNAL(clicked()), processWindow, SLOT(show()));
    connect(ui->saveControlsStatesButton, SIGNAL(clicked()), SLOT(slotSaveControls()));
    connect(ui->loadControlsStatesButton, SIGNAL(clicked()), SLOT(slotLoadControls()));

    manager->setScene(0);
    ui->scenesComboBox->setCurrentIndex(0);
    ui->scenesStackedWidget->setCurrentIndex(0);

    startTimer(500);

    qDebug() << "Constructor End: MainWindow";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveControls(Scene *scene, QString file, int state)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup("/"+scene->name());
        settings.beginGroup("/state"+QString::number(state, 2));
        for(int i=0; i<scene->getControls().count(); i++) {
            IControl *control = scene->getControls().at(i);
            settings.setValue(control->getName(), control->getData());
        }
        settings.endGroup();
    settings.endGroup();
}

void MainWindow::loadControls(Scene *scene, QString file, int state)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup("/"+scene->name());
        settings.beginGroup("/state"+QString::number(state));
        for(int i=0; i<scene->getControls().count(); i++) {
            IControl *control = scene->getControls().at(i);
            if (settings.contains(control->getName())) {
                QString value = settings.value(control->getName()).toString();
                control->setData(value);
            }
        }
        settings.endGroup();
    settings.endGroup();
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

void MainWindow::setFullScreen(bool full)
{
    if (full)
        manager->getView()->showFullScreen();
    else
        manager->getView()->showNormal();
}

void MainWindow::slotSaveControls()
{
    saveControls(manager->getCurScene(), "controls.ini", 0);
}

void MainWindow::slotLoadControls()
{
    loadControls(manager->getCurScene(), "controls.ini", 0);
}


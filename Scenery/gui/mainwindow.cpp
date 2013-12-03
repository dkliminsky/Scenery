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

    // Inputs
    ui->tableInputs->setRowCount(inputs.size());
    for (int i=0; i<inputs.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(tr("Camera %1").arg(i+1));
        ui->tableInputs->setItem(i, 0, item);
    }
    ui->tableInputs->resizeColumnsToContents();

    // Processes
    ui->tableProcesses->setRowCount(processes.size());
    for (int i=0; i<processes.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(processes.at(i)->getName());
        ui->tableProcesses->setItem(i, 0, item);
        processWindows += new ProcessWindow(processes.at(i), manager->name() + ".ini");
    }
    ui->tableProcesses->resizeColumnsToContents();
    connect(ui->tableProcesses, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::slotEditProcess);

    // Scenes
    ui->tableScenes->setRowCount(scenes.size());
    for (int i=0; i<scenes.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(scenes.at(i)->name());
        ui->tableScenes->setItem(i, 0, item);
        ui->tableScenes->setItem(i, 1, new QTableWidgetItem("0"));
    }
    ui->tableScenes->resizeColumnsToContents();
    connect(ui->tableScenes, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::slotChangeScene);

    // Scenes controls
    for(int i=0; i<scenes.size(); i++) {
        Scene *scene = scenes.at(i);

        QWidget *widget = new QWidget();
        QGridLayout *layout = new QGridLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        //layout->setSpacing(3);

        for (int j=0; j<scene->controls().size(); j++) {
            IControl *control = scene->controls().at(j);
            layout->addWidget(new QLabel(control->name()), j, 0);
            switch(control->type()) {
            case IControl::ControlBool:
                layout->addWidget(new ControlBoolWidget(static_cast<ControlBool *>(control)), j, 1);
                break;
            case IControl::ControlInt:
                layout->addWidget(new ControlIntWidget(static_cast<ControlInt *>(control)), j, 1);
                break;
            case IControl::ControlDouble:
                layout->addWidget(new ControlDoubleWidget(static_cast<ControlDouble *>(control)), j, 1);
                break;
            case IControl::ControlString:
                layout->addWidget(new ControlStringWidget(static_cast<ControlString *>(control)), j, 1);
                break;
            case IControl::ControlColor:
                layout->addWidget(new ControlColorWidget(static_cast<ControlColor *>(control)), j, 1);
                break;
            case IControl::ControlImage:
                // !!
                break;
            case IControl::ControlButton:
                layout->addWidget(new ControlButtonWidget(scenes.at(i),
                                  static_cast<ControlButton *>(control)), j, 1);
            }
        }

        if (layout->count() > 0)
            layout->setRowStretch(layout->count()-1, 1);

        widget->setLayout(layout);
        ui->controlsStackedWidget->addWidget(widget);
    }


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
    if (manager->getViews().size() > 0) {
        ui->tableScenes->setItem(curScene, 1,
                             new QTableWidgetItem(QString().number(manager->getViews().at(0)->fps())));
    }

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
    if (manager->getViews().size() > 0) {
        if (full)
            manager->getViews().at(0)->showFullScreen();
        else
            manager->getViews().at(0)->showNormal();
    }
}

void MainWindow::slotEditProcess(int row, int column)
{
    if ( column == 0) {
        processWindows.at(row)->show();
    }
    else if (column == 2) {
        for(int i=0; i<manager->getProcesses().size(); i++) {
            //manager->getProcesses().at(i)->setDebug(false);
            //ui->tableProcesses->setItem(i, 2, new QTableWidgetItem(""));
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


//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "tablebutton.h"

//#include <QSettings>
//#include <QDebug>

//MainWindow::MainWindow(Manager *manager, QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    qDebug() << "Constructor Begin: MainWindow";

//    ui->setupUi(this);
//    this->manager = manager;
//    loadSettings();

//    for(int i=0; i<manager->getScenes().size(); i++) {
//        Scene *scene = manager->getScenes().at(i);
//        ui->scenesComboBox->addItem(scene->name());
//        if (scene->getLayout()->count() > 0)
//            scene->getLayout()->setRowStretch(scene->getLayout()->count()-1, 1);
//        ui->scenesStackedWidget->addWidget(scene->getWidget());
//    }

//    processWindow = new ProcessWindow(manager->getProcesses().at(0), "process.ini");

//    connect(ui->scenesComboBox, SIGNAL(activated(int)), SLOT(changeScene(int)));
//    connect(ui->actionFullScreen, SIGNAL(toggled(bool)), SLOT(setFullScreen(bool)));
//    connect(ui->processParamButton, SIGNAL(clicked()), processWindow, SLOT(show()));
//    connect(ui->saveStateButton, SIGNAL(clicked()), SLOT(slotSaveControls()));
//    connect(ui->loadStateButton, SIGNAL(clicked()), SLOT(slotLoadControls()));
//    connect(ui->addStateButton, SIGNAL(clicked()), SLOT(slotAddState()));
//    connect(ui->delStateButton, SIGNAL(clicked()), SLOT(slotDelState()));

//    changeScene(0);
//    ui->scenesComboBox->setCurrentIndex(0);

//    startTimer(500);

//    qDebug() << "Constructor End: MainWindow";
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

//void MainWindow::saveControls(Scene *scene, QString file, int state, QString name)
//{
//    QSettings settings(file, QSettings::IniFormat);
//    settings.beginGroup("/"+scene->name());
//        settings.setValue("/state_name"+QString::number(state), name);
//        settings.beginGroup("/state"+QString::number(state));
//        for(int i=0; i<scene->getControls().count(); i++) {
//            IControl *control = scene->getControls().at(i);
//            settings.setValue(control->getName(), control->getData());
//        }
//        settings.endGroup();
//    settings.endGroup();
//}

//void MainWindow::loadControls(Scene *scene, QString file, int state)
//{
//    QSettings settings(file, QSettings::IniFormat);
//    settings.beginGroup("/"+scene->name());
//        settings.beginGroup("/state"+QString::number(state));
//        for(int i=0; i<scene->getControls().count(); i++) {
//            IControl *control = scene->getControls().at(i);
//            if (settings.contains(control->getName())) {
//                QString value = settings.value(control->getName()).toString();
//                control->setData(value);
//            }
//        }
//        settings.endGroup();
//    settings.endGroup();
//}

//QStringList MainWindow::loadControlsStates(Scene *scene, QString file)
//{
//    QStringList list;
//    QSettings settings(file, QSettings::IniFormat);
//    settings.beginGroup("/"+scene->name());
//    bool isState = true;
//    int i = 0;
//    while (isState) {
//        QString state = "/state_name"+QString::number(i);
//        if ( settings.contains(state))
//        {
//            list << settings.value(state).toString();
//            i++;
//        }
//        else {
//            isState = false;
//        }
//    }
//    settings.endGroup();

//    if (list.count() == 0)
//        list << "Default";

//    return list;
//}

//void MainWindow::closeEvent(QCloseEvent *)
//{
//    QSettings settings;
//    settings.setValue("MainWindow/Geometry", saveGeometry());
//    settings.setValue("MainWindow/State", saveState());
//    settings.setValue("View/Geometry", manager->getView()->saveGeometry());

//    qApp->exit(0);
//}

//void MainWindow::timerEvent(QTimerEvent *)
//{
//    ui->graphicFPSLabel->setNum(manager->getView()->getFPS());
//    ui->input1FPSLabel->setNum(manager->getInputs().at(0)->getFPS());
//}

//void MainWindow::loadSettings()
//{
//    QSettings settings;
//    restoreGeometry(settings.value("MainWindow/Geometry").toByteArray());
//    restoreState(settings.value("MainWindow/State").toByteArray());
//    manager->getView()->restoreGeometry(settings.value("View/Geometry").toByteArray());
//}

//void MainWindow::addState(QString name)
//{
//    QTableWidget *table = ui->controlsStatesTable;
//    int i = table->rowCount();
//    table->setRowCount(i + 1);

//    TableButton *button = new TableButton(i);
//    connect(button, SIGNAL(signalClicked(int)), SLOT(changeState(int)));
//    table->setCellWidget(i, 0, button);

//    QTableWidgetItem *item1 = new QTableWidgetItem(name);
//    table->setItem(i, 1, item1);
//}

//void MainWindow::delState(int n)
//{
//    if (n == 0)
//        return;

//    ui->controlsStatesTable->removeRow(n);

//    for (int i=0; i<ui->controlsStatesTable->rowCount(); i++) {
//        TableButton *button = new TableButton(i);
//        connect(button, SIGNAL(signalClicked(int)), SLOT(changeState(int)));
//        ui->controlsStatesTable->setCellWidget(i, 0, button);
//    }

//    changeState(n - 1);
//}

//void MainWindow::changeScene(int n)
//{
//    manager->setScene(n);
//    Scene *scene = manager->getCurScene();
//    loadControls(scene, "controls.ini", 0);
//    QStringList list = loadControlsStates(scene, "controls.ini");

//    ui->scenesStackedWidget->setCurrentIndex(n);
//    ui->controlsStatesTable->clearContents();
//    ui->controlsStatesTable->setRowCount(0);
//    for (int i=0; i<list.count(); ++i) {
//        addState(list.at(i));
//    }

//    changeState(0);
//}

//void MainWindow::changeState(int n)
//{
//    Q_ASSERT(n < ui->controlsStatesTable->rowCount());

//    curState = n;
//    for (int i=0; i<ui->controlsStatesTable->rowCount(); ++i) {
//        QTableWidgetItem *item = ui->controlsStatesTable->item(i, 1);
//        item->setIcon(QIcon());
//    }

//    ui->controlsStatesTable->item(n, 1)->setIcon(QIcon(":/icons/icons/play.png"));
//    loadControls(manager->getCurScene(), "controls.ini", n);
//}

//void MainWindow::setFullScreen(bool full)
//{
//    if (full)
//        manager->getView()->showFullScreen();
//    else
//        manager->getView()->showNormal();
//}

//void MainWindow::slotSaveControls()
//{
//    saveControls(manager->getCurScene(), "controls.ini", curState,
//                 ui->controlsStatesTable->item(curState, 1)->text());
//}

//void MainWindow::slotLoadControls()
//{
//    loadControls(manager->getCurScene(), "controls.ini", curState);
//}

//void MainWindow::slotAddState()
//{
//    addState("New state");
//}

//void MainWindow::slotDelState()
//{
//    delState(curState);
//}

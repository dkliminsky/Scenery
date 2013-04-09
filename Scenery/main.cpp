#include <QApplication>

#include "manager.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager manager;
    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

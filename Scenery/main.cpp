#include <QApplication>

#include "manager.h"
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Turlicht");
    QCoreApplication::setApplicationName("Scenery");
    Manager manager;
    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

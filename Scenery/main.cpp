#include <QApplication>

#include "gui/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("turlicht");
    QCoreApplication::setOrganizationDomain("turlicht.tk");
    QCoreApplication::setApplicationName("Scenery");

    MainWindow mainWindow(nullptr);
    mainWindow.show();
    return a.exec();
}

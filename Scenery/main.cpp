#include <QApplication>

#include "gui/mainwindow.h"
#include "scenes/VLMT/managervlmt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ManagerVLMT manager;

    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

#include <QApplication>

#include "gui/mainwindow.h"
#include "scenes/managervlmt.h"
#include "scenes/managertable.h"
#include "scenes/managerdance.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //ManagerVLMT manager;
    ManagerDance manager;
    //ManagerTable manager;

    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

#include <QApplication>

#include "gui/mainwindow.h"
#include "scenes/VLMT/managervlmt.h"
#include "scenes/table/managertable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //ManagerVLMT manager;
    ManagerTable manager;

    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

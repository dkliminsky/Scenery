#include <QApplication>

#include "gui/mainwindow.h"
#include "scenes/managervlmt.h"
#include "scenes/managerdk.h"
#include "scenes/managertable.h"
#include "scenes/managerdance.h"
#include "scenes/managermotion.h"
#include "scenes/manager2cameras.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //ManagerVLMT manager;
    //ManagerDK manager;
    ManagerDance manager;
    //ManagerTable manager;
    //ManagerMotion manager;
    //Manager2Cameras manager;

    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

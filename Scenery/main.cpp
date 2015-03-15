#include <QApplication>

#include "gui/mainwindow.h"

//#include "scenes/example_scene.cpp"
#include "scenes/dance.cpp"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("turlicht");
	QCoreApplication::setOrganizationDomain("turlicht.tk");
	QCoreApplication::setApplicationName("Scenery");

//    ExampleManager manager;
    KinectManager manager;
	
    manager.init();
    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

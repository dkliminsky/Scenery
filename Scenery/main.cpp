#include <QApplication>

#include "gui/mainwindow.h"

#include "scenes/examplemanager.h"
#include "scenes/examplekinectmanager.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("turlicht");
	QCoreApplication::setOrganizationDomain("turlicht.tk");
	QCoreApplication::setApplicationName("Scenery");

    //ExampleManager manager;
	ExampleKinectManager manager;
	
	
	manager.initScene();
    MainWindow mainWindow(&manager);
    mainWindow.show();
    return a.exec();
}

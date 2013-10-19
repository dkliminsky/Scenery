#include "managerdk.h"

ManagerDK::ManagerDK()
{
    int cameraWidth = 640;
    int cameraHeight = 480;

    inputs += new Input(Input::Camera, "",
                        cameraWidth, cameraHeight);
    cameraWidth = inputs.at(0)->getWidth();
    cameraHeight = inputs.at(0)->getHeight();

    processes += new Process("Motion", cameraWidth, cameraHeight);
    processes += new Process("Color", cameraWidth, cameraHeight);
    processes += new Process("IR Color", cameraWidth, cameraHeight);
    processes += new Process("Contour", cameraWidth, cameraHeight);
    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);

    QGLFormat format;
    format.setDoubleBuffer(false);
    views += new View(format);
    views.at(0)->datas()->append(processes.at(0));
    views.at(0)->datas()->append(processes.at(1));
    views.at(0)->datas()->append(processes.at(2));
    views.at(0)->datas()->append(processes.at(3));

    scenes += new Effect01();
    scenes += new Skeleton();
    scenes += new Cage();
    scenes += new Brush();
    scenes += new Strings();
    scenes += new Inking();

    views.at(0)->setScene(scenes.at(0));
    startTimer(17);
}

ManagerDK::~ManagerDK()
{
    delete debug;
}

void ManagerDK::timerEvent(QTimerEvent *)
{
    if ( !inputs.at(0)->isRunning() ) {
        // возвращается копия изображения,
        // можно сразу использовать
        IplImage *frame = inputs.at(0)->getFrame();

        if ( isProcessesComplete() ) {
            debug->show(frame, processes.at(0));
            debug->show(frame, processes.at(1));
            debug->show(frame, processes.at(2));
            debug->show(frame, processes.at(3));

            processesCopyData();

            processes.at(0)->setImage(frame);
            processes.at(1)->setImage(frame);
            processes.at(2)->setImage(frame);
            processes.at(3)->setImage(frame);

            processesStart();
        }
        inputs[0]->start();
    }

    views.at(0)->updateGL();
}

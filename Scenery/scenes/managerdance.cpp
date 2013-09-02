#include "managerdance.h"

ManagerDance::ManagerDance()
{
    int cameraWidth = 640;
    int cameraHeight = 480;

    inputs += new Input(Input::Camera, "",
                        cameraWidth, cameraHeight);
    cameraWidth = inputs.at(0)->getWidth();
    cameraHeight = inputs.at(0)->getHeight();

    processes += new Process("Video", cameraWidth, cameraHeight);
    processes += new Process("Motion", cameraWidth, cameraHeight);
    processes += new Process("Contour", cameraWidth, cameraHeight);

    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);

    QGLFormat format;
    format.setDoubleBuffer(false);
    views += new View(format);
    views.at(0)->datas()->append(processes.at(0));
    views.at(0)->datas()->append(processes.at(1));
    views.at(0)->datas()->append(processes.at(2));

    scenes += new Memorize();
    scenes += new DanceEffects();
    scenes += new Shift();
    scenes += new Skeleton();

    views.at(0)->setScene(scenes.at(0));
    startTimer(17);
}

void ManagerDance::timerEvent(QTimerEvent *)
{
    if ( !inputs.at(0)->isRunning() ) {
        IplImage *frame = inputs.at(0)->getFrame();

        if ( isProcessesComplete() ) {

            // Debug process
            debug->show(frame, processes.at(0));
            debug->show(frame, processes.at(1));
            debug->show(frame, processes.at(2));

            processesCopyData();
            //
            processes.at(0)->setImage(frame);
            processes.at(1)->setImage(frame);
            processes.at(2)->setImage(frame);

            processesStart();
        }
        inputs[0]->start();
    }
    views.at(0)->updateGL();
}

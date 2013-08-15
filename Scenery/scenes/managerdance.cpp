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

    scenes += new DanceEffects();
    scenes += new Shift();
    scenes += new Skeleton();

    views.at(0)->datas()->resize(3);
    views.at(0)->datas()->at(0).width = cameraWidth;
    views.at(0)->datas()->at(0).height = cameraHeight;
    views.at(0)->datas()->at(0).image = cvCreateImage(cvSize(cameraWidth, cameraHeight), IPL_DEPTH_8U, 3);
    views.at(0)->datas()->at(1).width = cameraWidth;
    views.at(0)->datas()->at(1).height = cameraHeight;
    views.at(0)->datas()->at(2).width = cameraWidth;
    views.at(0)->datas()->at(2).height = cameraHeight;

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

            //
            processes.at(0)->setImage(frame);
            processes.at(1)->setImage(frame);
            processes.at(2)->setImage(frame);

            // set process data in scene
            cvCopy(processes.at(0)->getImage(), views.at(0)->datas()->at(0).image);
            views.at(0)->datas()->at(1).areas = processes.at(1)->getAreas();
            views.at(0)->datas()->at(1).seqAreas = processes.at(1)->getSeqAreas();
            views.at(0)->datas()->at(2).areas = processes.at(2)->getAreas();
            views.at(0)->datas()->at(2).seqAreas = processes.at(2)->getSeqAreas();

            processesStart();
        }
        inputs[0]->start();
    }
    views.at(0)->updateGL();
}

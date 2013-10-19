#include "managermotion.h"

ManagerMotion::ManagerMotion()
{
    int cameraWidth = 640;
    int cameraHeight = 360;

    inputs += new Input(Input::Camera, "",
                        cameraWidth, cameraHeight);
    cameraWidth = inputs.at(0)->getWidth();
    cameraHeight = inputs.at(0)->getHeight();

    processes += new Process("Motion", cameraWidth, cameraHeight);
    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);
    server = new Server(this);

    startTimer(32);
}

void ManagerMotion::timerEvent(QTimerEvent *)
{
    if ( !inputs.at(0)->isRunning() ) {
        IplImage *frame = inputs.at(0)->getFrame();

        if ( isProcessesComplete() ) {

            // Debug process
            debug->show(frame, processes.at(0));

            processesCopyData();

            //qDebug() << "server start";
            server->wait();
            server->setSeqAreas(processes[0]->getSeqAreas());
            server->start();

            //
            processes.at(0)->setImage(frame);
            processesStart();
        }
        inputs[0]->start();
    }
}

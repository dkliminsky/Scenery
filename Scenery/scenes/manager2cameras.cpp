#include "manager2cameras.h"

Manager2Cameras::Manager2Cameras()
{
    int cameraWidth1 = 320;
    int cameraHeight1 = 240;
    inputs += new Input(Input::Camera, "0",
                        cameraWidth1, cameraHeight1);
    cameraWidth1 = inputs.at(0)->getWidth();
    cameraHeight1 = inputs.at(0)->getHeight();



    int cameraWidth2 = 320;
    int cameraHeight2 = 240;
    inputs += new Input(Input::Camera, "1",
                        cameraWidth2, cameraHeight2);
    cameraWidth2 = inputs.at(1)->getWidth();
    cameraHeight2 = inputs.at(1)->getHeight();


    processes += new Process("Motion 1", cameraWidth1, cameraHeight1);
    processes += new Process("Motion 2", cameraWidth2, cameraHeight2);
    debug0 = new ProcessDebug("Debug 1", cameraWidth1, cameraHeight1);
    debug1 = new ProcessDebug("Debug 2", cameraWidth2, cameraHeight2);
    server = new Server(this);

    startTimer(32);
}

void Manager2Cameras::timerEvent(QTimerEvent *)
{
    if ( isInputsComplete() ) {
        IplImage *frame0 = inputs.at(0)->getFrame();
        IplImage *frame1 = inputs.at(1)->getFrame();

        if ( isProcessesComplete() ) {

            // Debug process
            debug0->show(frame0, processes.at(0));
            debug1->show(frame1, processes.at(1));

            processesCopyData();

            //qDebug() << "server start";
            server->wait();
            //server->setSeqAreas(processes[0]->getSeqAreas());
            server->setAreas(0, processes[0]->getAreas());
            server->setAreas(1, processes[1]->getAreas());

            server->start();

            //
            processes.at(0)->setImage(frame0);
            processes.at(1)->setImage(frame1);
            processesStart();
        }
        inputs[0]->start();
        inputs[1]->start();
    }
}

#include "managertable.h"

ManagerTable::ManagerTable()
{
    int cameraWidth = 640;
    int cameraHeight = 480;

    inputs += new Input(Input::Camera, "",
                        cameraWidth, cameraHeight);
    cameraWidth = inputs.at(0)->getWidth();
    cameraHeight = inputs.at(0)->getHeight();

    processes += new Process("Circle", cameraWidth, cameraHeight);
    processes += new Process("Red", cameraWidth, cameraHeight);
    processes += new Process("Green", cameraWidth, cameraHeight);
    processes += new Process("Blue", cameraWidth, cameraHeight);
    processes += new Process("Yellow", cameraWidth, cameraHeight);
    processes += new Process("Orange", cameraWidth, cameraHeight);

    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);

    QGLFormat format;
    format.setDoubleBuffer(false);
    views += new View(format);
    views.at(0)->datas()->append(processes.at(0));
    views.at(0)->datas()->append(processes.at(1));
    views.at(0)->datas()->append(processes.at(2));
    views.at(0)->datas()->append(processes.at(3));
    views.at(0)->datas()->append(processes.at(4));
    views.at(0)->datas()->append(processes.at(5));

    scenes += new Fractals();

    views.at(0)->setScene(scenes.at(0));
    startTimer(17);
}

void ManagerTable::timerEvent(QTimerEvent *)
{
    if ( !inputs.at(0)->isRunning() ) {
        // возвращается копия изображения,
        // можно сразу использовать
        IplImage *frame = inputs.at(0)->getFrame();

        if ( isProcessesComplete() ) {

            // Debug process
            debug->show(frame, processes.at(0));
            debug->show(frame, processes.at(1));
            debug->show(frame, processes.at(2));
            debug->show(frame, processes.at(3));
            debug->show(frame, processes.at(4));
            debug->show(frame, processes.at(5));

            processesCopyData();

            processes.at(0)->setImage(frame);
            processes.at(1)->setImage(frame);
            processes.at(2)->setImage(frame);
            processes.at(3)->setImage(frame);
            processes.at(4)->setImage(frame);
            processes.at(5)->setImage(frame);

            processesStart();
        }
        inputs[0]->start();
    }

    views.at(0)->updateGL();
}

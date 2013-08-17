#include "managervlmt.h"

ManagerVLMT::ManagerVLMT()
{
    int cameraWidth = 640;
    int cameraHeight = 480;

    inputs += new Input(Input::Camera, "",
                        cameraWidth, cameraHeight);
    cameraWidth = inputs.at(0)->getWidth();
    cameraHeight = inputs.at(0)->getHeight();

    processes += new Process("Motion", cameraWidth, cameraHeight);
    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);

    QGLFormat format;
    format.setDoubleBuffer(false);
    views += new View(format);
    views.at(0)->datas()->append(processes.at(0));

    scenes += new Skeleton();
    scenes += new Cage();
    scenes += new Brush();
    scenes += new Strings();
    scenes += new Inking();

    views.at(0)->setScene(scenes.at(0));
    startTimer(17);
}

ManagerVLMT::~ManagerVLMT()
{
    delete debug;
}

void ManagerVLMT::timerEvent(QTimerEvent *)
{
    if ( !inputs.at(0)->isRunning() ) {
        // возвращается копия изображения,
        // можно сразу использовать
        IplImage *frame = inputs.at(0)->getFrame();

        if ( !processes.at(0)->isRunning() ) {
            debug->show(frame, processes.at(0));
            processes.at(0)->setImage(frame);
            processes.at(0)->start();
        }
        inputs[0]->start();
    }

    views.at(0)->updateGL();
}

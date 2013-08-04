#include "managervlmt.h"

ManagerVLMT::ManagerVLMT()
{
    int cameraWidth = 640;
    int cameraHeight = 480;

    inputs += new Input(Input::Camera, "", cameraWidth, cameraHeight);
    cameraWidth = inputs.at(0)->getWidth();
    cameraHeight = inputs.at(0)->getHeight();

    processes += new Process(cameraWidth, cameraHeight);
    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);

    QGLFormat format;
    format.setDoubleBuffer(false);
    views += new View(format);

    scenes += new Skeleton();
    scenes += new Cage();
    scenes += new Brush();
    scenes += new Strings();
    scenes += new Inking();

    views.at(0)->setScene(scenes.at(3));

    views.at(0)->datas()->resize(1);
    views.at(0)->datas()->at(0).width = 640;
    views.at(0)->datas()->at(0).height = 480;

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
            // Debug process
            debug->show(frame, processes.at(0));

            //
            processes.at(0)->setImage(frame);

            // set process data in scene
            views.at(0)->datas()->at(0).areas = processes.at(0)->getAreas();
            views.at(0)->datas()->at(0).seqAreas = processes.at(0)->getSeqAreas();
            views.at(0)->datas()->at(0).contours = processes.at(0)->getContours();

            processes.at(0)->start();
        }
        inputs[0]->start();

        // set video stream in scene
        // ...
    }

    views.at(0)->updateGL();
}

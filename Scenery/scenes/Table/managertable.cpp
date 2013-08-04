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

    debug = new ProcessDebug("Debug", cameraWidth, cameraHeight);

    QGLFormat format;
    format.setDoubleBuffer(false);
    views += new View(format);

    scenes += new Fractals();

    views.at(0)->setScene(scenes.at(0));

    views.at(0)->datas()->resize(4);
    views.at(0)->datas()->at(0).width = cameraWidth;
    views.at(0)->datas()->at(0).height = cameraHeight;
    views.at(0)->datas()->at(1).width = cameraWidth;
    views.at(0)->datas()->at(1).height = cameraHeight;
    views.at(0)->datas()->at(2).width = cameraWidth;
    views.at(0)->datas()->at(2).height = cameraHeight;
    views.at(0)->datas()->at(3).width = cameraWidth;
    views.at(0)->datas()->at(3).height = cameraHeight;

    startTimer(17);
}

void ManagerTable::timerEvent(QTimerEvent *)
{
    if ( !inputs.at(0)->isRunning() ) {
        // возвращается копия изображения,
        // можно сразу использовать
        IplImage *frame = inputs.at(0)->getFrame();

        if ( !processes.at(0)->isRunning() &&
             !processes.at(1)->isRunning() &&
             !processes.at(2)->isRunning() &&
             !processes.at(3)->isRunning() ) {

            // Debug process
            debug->show(frame, processes.at(0));
            debug->show(frame, processes.at(1));
            debug->show(frame, processes.at(2));
            debug->show(frame, processes.at(3));

            //
            processes.at(0)->setImage(frame);
            processes.at(1)->setImage(frame);
            processes.at(2)->setImage(frame);
            processes.at(3)->setImage(frame);

            // set process data in scene
            views.at(0)->datas()->at(0).areas = processes.at(0)->getAreas();
            views.at(0)->datas()->at(1).areas = processes.at(1)->getAreas();
            views.at(0)->datas()->at(2).areas = processes.at(2)->getAreas();
            views.at(0)->datas()->at(3).areas = processes.at(3)->getAreas();

            processes.at(0)->start();
            processes.at(1)->start();
            processes.at(2)->start();
            processes.at(3)->start();
        }
        inputs[0]->start();
    }

    views.at(0)->updateGL();
}

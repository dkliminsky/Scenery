#include "managertv.h"

ManagerTV::ManagerTV()
{
}

ManagerTV::~ManagerTV()
{

}

void ManagerTV::timerEvent(QTimerEvent *)
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

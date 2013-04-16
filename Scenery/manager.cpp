#include "manager.h"

#include <QDebug>
#include <QDir>
#include <QEvent>
#include <QApplication>

Manager::Manager()
{
    qDebug() << "Constructor Begin: Manager";

    isPlay = false;
    ProcessTools::initRGB2HSV();
    int cameraWidth = 640;
    int cameraHeight = 480;

    Input *input = new Input(Input::None, "", cameraWidth, cameraHeight);
    //InputThread *input = new InputThread(InputThread::Video, "video/tesla.mp4");
    //input->start();
    inputs.append(input);

    Process *process = new Process(input->getWidth(), input->getHeigth());
    processes.append(process);

    debug = new DebugWindow("main", cameraWidth, cameraHeight);

    scenes.append(new Skeleton());
    scenes.append(new Cage());
    scenes.append(new Strings());
    scenes.append(new Brush());
    scenes.append(new Inking());

    QGLFormat format;
    format.setDoubleBuffer(false);
    view = new View(format);
    view->show();
    setScene(0);

    firstInput = true;
    firstDebug = true;
    firstSetImage = true;
    firstSetData = true;
    firstProcess = true;
    firstEndProcess = true;

    qDebug() << "Input run";
    input->start();
    startTimer(17);
    qDebug() << "Constructor End: Manager";
}

Manager::~Manager()
{
    qDebug() << "Destructor Begin: Manager";

    delete view;

    for ( int i=0; i<processes.size(); i++){
        processes[i]->wait();
        delete processes[i];
    }

    for ( int i=0; i<inputs.size(); i++){
        inputs[i]->wait();
        delete inputs[i];
    }

    for ( int i=0; i<scenes.size(); i++){
        delete scenes[i];
    }

    qDebug() << "Destructor End: Manager";
}

void Manager::setScene(int n)
{
    if ( !(n < scenes.size()) )
        return;

    curScene = n;
    view->setScene(scenes.at(n));
    scenes.at(n)->setWidth(0, processes[0]->getWidth());
    scenes.at(n)->setHeight(0, processes[0]->getHeight());
}

void Manager::timerEvent(QTimerEvent *)
{
    step();
}

void Manager::step()
{
    if ( !inputs[0]->isRunning() ) {

        if (firstInput) {
            qDebug() << "First Input";
            firstInput = false;
        }

        // возвращается копия изображения
        //
        IplImage *frame = inputs[0]->getFrame();

        if ( !processes[0]->isRunning() ) {

            if (firstDebug) {
                qDebug() << "First Debug";
                firstDebug = false;
            }

            debug->show(frame, processes[0]);

            if (firstSetImage) {
                qDebug() << "First Set Image";
                firstSetImage = false;
            }

            processes[0]->setImage(frame);

            if (firstSetData) {
                qDebug() << "First Set Data";
                firstSetData = false;
            }

            // set process data in scene
            scenes.at(curScene)->setAreas(0, processes[0]->getAreas());
            scenes.at(curScene)->setSeqAreas(0, processes[0]->getSeqAreas());
            scenes.at(curScene)->setContours(0, processes[0]->getContours());

            if (firstProcess) {
                qDebug() << "First Process";
                firstProcess = false;
            }

            processes[0]->start();

            if (firstEndProcess) {
                qDebug() << "First End Process";
                firstEndProcess = false;
            }
        }

        inputs[0]->start();

        // set video stream in scene
    }

    view->updateGL();
}


#ifndef INPUT_H
#define INPUT_H

#include <QThread>
#include <QString>
#include <QTime>
#include <opencv/highgui.h>

#define STORE_FRAMES 3

class Input: public QThread
{
public:

    enum Device {
        None,
        Camera,
        Video
    };

    Input(Device device, QString name, int width = 0, int height = 0);
    ~Input();

    IplImage* getFrame() { return frame; }

    int getWidth() { return width;}
    int getHeigth() { return height;}

    int getFPS() { return fpsResult; }

protected:
    void run();

private:
    Device device;
    QString name;
    int width;
    int height;
    CvCapture *capture;

    int curFrame;
    IplImage *arrFrame[STORE_FRAMES];
    IplImage *frame;

    void initCamera();
    void initVideo();

    QTime fpsTime;
    int fpsRest;
    int fpsFrames;
    int fpsResult;
};

#endif // INPUT_H

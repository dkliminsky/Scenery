#ifndef TASKS_H
#define TASKS_H

#include <QString>
#include <QThread>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>

class Tasks : public QThread
{
    Q_OBJECT
public:
    void run();

    static void saveImage(IplImage *image, const QString &fileName);
    static void loadImage(IplImage *image, const QString &fileName);

signals:
    
public slots:
    
};

#endif // TASKS_H

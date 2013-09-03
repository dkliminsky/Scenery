#ifndef MEMORIZE_H
#define MEMORIZE_H

#include "graphics/scene.h"

#define COUNT_RECORDS 5

class Memorize : public Scene
{
public:
    Memorize();
    QString name() { return "Memorize"; }

    void paint();
    void action(int id);

private:
    int w;
    int h;

    int queueManualLength;
    QQueue<Image *> queueManual;

    struct Record {
        QQueue<Image *> queue;
        bool isRecord;
        int repeats;
        int playFrame;
    };
    QVector<Record> records;

    void addFrameToQueue(QQueue<Image *> *queue, Image *frame);
    void mergeFrames(Image *frame, Image *alpha);
    uchar blendValues(uchar c1, uchar c2);

    void stepQueueManual(Image *frame);
    void stepQueueRecord(Image *frame);

};

#endif // MEMORIZE_H

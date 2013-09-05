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
    Image *frameCopy;

    int queueManualLength;
    QQueue<Image *> queueManual;
    QVector<Image *> vectorMulti;

    struct MultiRecord {
        //QQueue<Image *> queue;
        bool isRecord;
        bool isPlay;
        int count;
        int record;
        int play;

        int repeats;
//        int playFrame;
//        int saveFrame;
    } mRecord;

    struct Record {
        //QQueue<Image *> queue;
        bool isRecord;
        int repeats;
        int playFrame;
        int saveFrame;
    };
    QVector<Record> records;

    void addFrameToQueue(QQueue<Image *> *queue, Image *frame);
    void saveFrame(int nQueue, int nFrame, Image *frame, Image *hit);
    Image *loadFrame(int nQueue, int nFrame);

    void mergeFrames(Image *frame, Image *alpha);
    void blendFrames(Image *frame, Image *alpha);
    void mulHit(Image *hit, Image *alpha);

    uchar blendValues(uchar c1, uchar c2);

    void stepQueueManual(Image *frame);
    void stepQueueMultiRecord(Image *frame);
    void stepQueueRecord(Image *frame);

};

#endif // MEMORIZE_H

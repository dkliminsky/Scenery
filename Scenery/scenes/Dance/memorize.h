#ifndef MEMORIZE_H
#define MEMORIZE_H

#include "graphics/scene.h"

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
    QString personDouble;
    int displacement;

    Image *storeMulti;

    struct MultiRecord {
        //QQueue<Image *> queue;
        bool isRecord;
        bool isPlay;
        int count;
        int countPlay;

        int record;
        int play;

        int repeats;
    } mRecord;

    void addFrameToQueue(QQueue<Image *> *queue, Image *frame);
    void saveFrame(int nQueue, int nFrame, Image *frame, Image *hit);
    Image *loadFrame(int nQueue, int nFrame);

    void mergeFrames(Image *frame, Image *alpha);
    void blendFrames(Image *frame, Image *alpha);
    void unionHit(Image *hit, Image *alpha);
    uchar blendValues(uchar c1, uchar c2);

    void stepQueueManual(Image *frame);
    void stepQueueMultiRecord(Image *frame, Image *hit);
    void stepPersonDouble(Image *frame, Image *hit);

};

#endif // MEMORIZE_H

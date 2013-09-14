#include "memorize.h"

Memorize::Memorize()
{
    control(queueManualLength=0, "Queue Length", 0, 500);
    button("Common", 1000, "Start Subtraction", 1001, "Stop Subtraction");
    button("MultiRecord", 1100, "Record", 1101, "Stop", 1102, "Repeat", 1103, "Forewer", 1104, "Break");
    control(personDouble="None", "Person Double", QStringList() << "None" << "Left" << "Right");
    control(displacement=0, "Displacement", 0, 20);

    mRecord.isRecord = false;
    mRecord.isPlay = false;
    mRecord.count = 0;
    mRecord.play = 0;
    mRecord.record = 0;
    mRecord.repeats = 0;
    storeMulti = 0;
}

void Memorize::paint()
{
    if (process(0)->isUpdate()) {
        w = process(0)->width();
        h = process(0)->height();
        Image *frame = process(0)->image();
        Image *hit = process(0)->hit();
        size(w, h);

        if (storeMulti) {
            storeMulti->saveWait();
            delete storeMulti;
            storeMulti = 0;
        }

        stepQueueManual(frame);
        stepQueueMultiRecord(frame, hit);
        stepPersonDouble(frame, hit);

        frame->bind();
        color(1,1,1,1);
        image(frame, w/2, h/2, w, h);
        flush();
    }
}

void Memorize::action(int id)
{
    if ( id == 1000 ) {
        process(0)->command("SubtractionImageStart");
    }
    else if ( id == 1001 ) {
        process(0)->command("SubtractionImageStop");
    }
    else if ( id == 1100 ) { // Record
        mRecord.isRecord = true;
        mRecord.record = mRecord.play;
    }
    else if ( id == 1101 ) { // Stop
        mRecord.isRecord = false;
        mRecord.record = 0;
    }
    else if ( id == 1102 ) { // Repeat
        //mRecord.isRecord = false;
        mRecord.isPlay = true;
        mRecord.play = 0;
        mRecord.repeats = 1;
        mRecord.countPlay = mRecord.count;
    }
    else if ( id == 1103 ) { // Forever
        //mRecord.isRecord = false;
        mRecord.isPlay = true;
        mRecord.play = 0;
        mRecord.repeats = -1;
        mRecord.countPlay = mRecord.count;
    }
    else if ( id == 1104 ) { // Break
        mRecord.isRecord = false;
        mRecord.isPlay = false;
        mRecord.play = 0;
        mRecord.record = 0;
        mRecord.repeats = 0;
    }
}

void Memorize::addFrameToQueue(QQueue<Image *> *queue, Image *frame)
{
    Q_ASSERT(frame->channels() == 3);
    Image *store = new Image(w, h, 4);
    int cFrame = frame->channels();
    int cStore = store->channels();
    for( int y=0; y<h; y++ ) {
        uchar*   hit_ptr = (uchar*) (process(0)->hit()->data() + y * process(0)->hit()->step());
        uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
        uchar* store_ptr = (uchar*) (store->data() + y * store->step());
        for( int x=0; x<w; x++ ) {
            store_ptr[cStore*x + 0] = frame_ptr[cFrame*x + 0];
            store_ptr[cStore*x + 1] = frame_ptr[cFrame*x + 1];
            store_ptr[cStore*x + 2] = frame_ptr[cFrame*x + 2];
            store_ptr[cStore*x + 3] = hit_ptr[x];
        }
    }

    queue->enqueue(store);
}

void Memorize::saveFrame(int nQueue, int nFrame, Image *frame, Image *hit)
{
    Q_ASSERT(frame->channels() == 3);
    Q_ASSERT(hit->channels() == 1);

    storeMulti = new Image(w, h, 4);
    int cFrame = frame->channels();
    int cStore = storeMulti->channels();
    for( int y=0; y<h; y++ ) {
        uchar*   hit_ptr = (uchar*) (hit->data()   + y * hit->step());
        uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
        uchar* store_ptr = (uchar*) (storeMulti->data() + y * storeMulti->step());
        for( int x=0; x<w; x++ ) {
            store_ptr[cStore*x + 0] = frame_ptr[cFrame*x + 0];
            store_ptr[cStore*x + 1] = frame_ptr[cFrame*x + 1];
            store_ptr[cStore*x + 2] = frame_ptr[cFrame*x + 2];
            store_ptr[cStore*x + 3] = hit_ptr[x];
        }
    }

    QString file = QString("d:\\memorize\\%1\\frame-%2.png").arg(nQueue).arg(nFrame);
    storeMulti->saveThread(file);
}

Image *Memorize::loadFrame(int nQueue, int nFrame)
{
    QString file = QString("d:\\memorize\\%1\\frame-%2.png").arg(nQueue).arg(nFrame);
    return new Image(file);
}

void Memorize::mergeFrames(Image *frame, Image *alpha)
{
    Q_ASSERT(alpha->channels() == 4);
    Q_ASSERT(frame->channels() == 3);

    int cFrame = frame->channels();
    int cAlpha = alpha->channels();

    for( int y=0; y<h; y++ ) {
        uchar*   hit_ptr = (uchar*) (process(0)->hit()->data() + y * process(0)->hit()->step());
        uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
        uchar* alpha_ptr = (uchar*) (alpha->data() + y * alpha->step());
        for( int x=0; x<w; x++ ) {
            if (alpha_ptr[cAlpha*x + 3]) {
                if (!hit_ptr[x]) {
                    frame_ptr[cFrame*x + 0] = alpha_ptr[cAlpha*x + 0];
                    frame_ptr[cFrame*x + 1] = alpha_ptr[cAlpha*x + 1];
                    frame_ptr[cFrame*x + 2] = alpha_ptr[cAlpha*x + 2];
                }
            }
        }
    }
}

void Memorize::blendFrames(Image *frame, Image *alpha)
{
    Q_ASSERT(alpha->channels() == 4);
    Q_ASSERT(frame->channels() >= 3);

    int cFrame = frame->channels();
    int cAlpha = alpha->channels();

    for( int y=0; y<h; y++ ) {
        uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
        uchar* alpha_ptr = (uchar*) (alpha->data() + y * alpha->step());
        for( int x=0; x<w; x++ ) {
            frame_ptr[cFrame*x + 0] = blendValues(frame_ptr[cFrame*x + 0], alpha_ptr[cAlpha*x + 0]);
            frame_ptr[cFrame*x + 1] = blendValues(frame_ptr[cFrame*x + 1], alpha_ptr[cAlpha*x + 1]);
            frame_ptr[cFrame*x + 2] = blendValues(frame_ptr[cFrame*x + 2], alpha_ptr[cAlpha*x + 2]);
        }
    }
}

void Memorize::unionHit(Image *hit, Image *alpha)
{
    Q_ASSERT(alpha->channels() == 4);
    Q_ASSERT(hit->channels() == 1);

    int cAlpha = alpha->channels();

    for( int y=0; y<h; y++ ) {
        uchar*   hit_ptr = (uchar*) (hit->data()   + y *   hit->step());
        uchar* alpha_ptr = (uchar*) (alpha->data() + y * alpha->step());
        for( int x=0; x<w; x++ ) {
            hit_ptr[x] = hit_ptr[x] | alpha_ptr[cAlpha*x + 3];
        }
    }
}

uchar Memorize::blendValues(uchar c1, uchar c2)
{
    uint i1 = (uint)(c1);
    uint i2 = (uint)(c2);
    return (i1 + i2) / 2;
}

void Memorize::stepQueueManual(Image *frame)
{
    addFrameToQueue(&queueManual, frame);
    if (queueManual.size() < queueManualLength) {
        addFrameToQueue(&queueManual, frame);
    }

    if (queueManual.size() > queueManualLength) {
        delete queueManual.dequeue();
    }

    if (queueManual.size()) {
        Image *store = queueManual.dequeue();
        blendFrames(frame, store);
        delete store;
    }
}

void Memorize::stepQueueMultiRecord(Image *frame, Image *hit)
{
    if (mRecord.isPlay) {
        if (mRecord.play >= mRecord.countPlay) {
            mRecord.play = 0;
            if (mRecord.repeats > 0) {
                mRecord.repeats--;
            }

            if (mRecord.repeats == 0) {
                mRecord.isPlay = false;
            }
        }
    }

    if (mRecord.isPlay) {
        Image *store = loadFrame(0, mRecord.play);
        mergeFrames(frame, store);

        if (mRecord.isRecord) {
            unionHit(hit, store);
        }

        delete store;
        mRecord.record = mRecord.play;
        mRecord.play++;
    }

    if (mRecord.isRecord) {
        saveFrame(0, mRecord.record, frame, hit);
        mRecord.record++;
        if (mRecord.count <= mRecord.record) {
            mRecord.count = mRecord.record;
        }
    }
}

void Memorize::stepPersonDouble(Image *frame, Image *hit)
{
    if (personDouble == "Left") {
        int cFrame = frame->channels();

        for( int y=0; y<h; y+=2 ) {
            uchar*   hit_ptr = (uchar*) (hit->data()   + y * hit->step());
            uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
            for( int x=0; x<w/2; x++ ) {
                int x2 = w - x;
                if (hit_ptr[x]) {
                    frame_ptr[cFrame*x2 + 0] = frame_ptr[cFrame*x + 0];
                    frame_ptr[cFrame*x2 + 1] = frame_ptr[cFrame*x + 1];
                    frame_ptr[cFrame*x2 + 2] = frame_ptr[cFrame*x + 2];
                }
            }
        }

        for( int y=1; y<h; y+=2 ) {
            uchar*   hit_ptr = (uchar*) (hit->data()   + y * hit->step());
            uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
            for( int x=0; x<w/2; x++ ) {
                int x2 = w - x - displacement;
                if (hit_ptr[x]) {
                    frame_ptr[cFrame*x2 + 0] = frame_ptr[cFrame*x + 0];
                    frame_ptr[cFrame*x2 + 1] = frame_ptr[cFrame*x + 1];
                    frame_ptr[cFrame*x2 + 2] = frame_ptr[cFrame*x + 2];
                }
            }

            for( int x=0; x<w/2; x++ ) {
                if (hit_ptr[x]) {
                    frame_ptr[cFrame*x + 0] = frame_ptr[cFrame*(x+displacement) + 0];
                    frame_ptr[cFrame*x + 1] = frame_ptr[cFrame*(x+displacement) + 1];
                    frame_ptr[cFrame*x + 2] = frame_ptr[cFrame*(x+displacement) + 2];
                }
            }
        }
    }
    if (personDouble == "Right") {
        int cFrame = frame->channels();

        for( int y=0; y<h; y+=2 ) {
            uchar*   hit_ptr = (uchar*) (hit->data()   + y * hit->step());
            uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
            for( int x=w/2; x<w; x++ ) {
                int x2 = w - x;
                if (hit_ptr[x]) {
                    frame_ptr[cFrame*x2 + 0] = frame_ptr[cFrame*x + 0];
                    frame_ptr[cFrame*x2 + 1] = frame_ptr[cFrame*x + 1];
                    frame_ptr[cFrame*x2 + 2] = frame_ptr[cFrame*x + 2];
                }
            }
        }

        for( int y=1; y<h; y+=2 ) {
            uchar*   hit_ptr = (uchar*) (hit->data()   + y * hit->step());
            uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
            for( int x=w/2; x<w; x++ ) {
                int x2 = w - x + displacement;
                if (hit_ptr[x]) {
                    frame_ptr[cFrame*x2 + 0] = frame_ptr[cFrame*x + 0];
                    frame_ptr[cFrame*x2 + 1] = frame_ptr[cFrame*x + 1];
                    frame_ptr[cFrame*x2 + 2] = frame_ptr[cFrame*x + 2];
                }
            }

            for( int x=w-1; x>=w/2; x-- ) {
                if (hit_ptr[x]) {
                    frame_ptr[cFrame*x + 0] = frame_ptr[cFrame*(x-displacement) + 0];
                    frame_ptr[cFrame*x + 1] = frame_ptr[cFrame*(x-displacement) + 1];
                    frame_ptr[cFrame*x + 2] = frame_ptr[cFrame*(x-displacement) + 2];
                }
            }
        }
    }
}


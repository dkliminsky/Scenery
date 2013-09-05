#include "memorize.h"

Memorize::Memorize()
{
    control(queueManualLength=0, "Queue Length", 0, 500);
    button("Common", 1000, "Start Subtraction", 1001, "Stop Subtraction");
    button("MultiRecord", 1100, "Record", 1101, "Stop", 1102, "Repeat", 1103, "Forewer");

    mRecord.isRecord = false;
    mRecord.isPlay = false;
    mRecord.count = 0;
    mRecord.play = 0;
    mRecord.record = 0;
    mRecord.repeats = 0;

    for (int i=0; i<COUNT_RECORDS; i++) {
        Record record;
        record.isRecord = false;
        record.repeats = 0;
        record.playFrame = 0;
        records += record;
        button("Store", i*10 + 0, "Record",
                        i*10 + 1, "Stop",
                        i*10 + 2, "Repeat",
                        i*10 + 3, "Forewer");
    }
}

void Memorize::paint()
{
    if (process(0)->isUpdate()) {
        w = process(0)->width();
        h = process(0)->height();
        Image *frame = process(0)->image();
        size(w, h);

        stepQueueManual(frame);
        stepQueueMultiRecord(frame);
        //stepQueueRecord(frame);

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
    else if ( id == 1100 ) {
        mRecord.isRecord = true;
        mRecord.record = mRecord.play;
    }
    else if ( id == 1101 ) {
        mRecord.isRecord = false;
        mRecord.isPlay = false;
        mRecord.play = 0;
        mRecord.record = 0;
        mRecord.repeats = 0;
    }
    else if ( id == 1102 ) {
        mRecord.isPlay = true;
        mRecord.play = 0;
        mRecord.repeats = 1;
    }
    else if ( id == 1103 ) {
        mRecord.isPlay = true;
        mRecord.play = 0;
        mRecord.repeats = -1;
    }
    else if (id < 1000) {
        int command = id % 10;
        int n = (id - command) / 10;
        if (command == 0) {
            records[n].isRecord = true;
            records[n].saveFrame = 0;
            records[n].playFrame = 0;
        }
        else if (command == 1) {
            records[n].isRecord = false;
            records[n].playFrame = 0;
            records[n].repeats = 0;
        }
        else if (command == 2) {
            records[n].isRecord = false;
            records[n].playFrame = 0;
            records[n].repeats = 1;
        }
        else if (command == 3) {
            records[n].isRecord = false;
            records[n].playFrame = 0;
            records[n].repeats = -1;
        }
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

    Image *store = new Image(w, h, 4);
    int cFrame = frame->channels();
    int cStore = store->channels();
    for( int y=0; y<h; y++ ) {
        uchar*   hit_ptr = (uchar*) (hit->data()   + y * hit->step());
        uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
        uchar* store_ptr = (uchar*) (store->data() + y * store->step());
        for( int x=0; x<w; x++ ) {
            store_ptr[cStore*x + 0] = frame_ptr[cFrame*x + 0];
            store_ptr[cStore*x + 1] = frame_ptr[cFrame*x + 1];
            store_ptr[cStore*x + 2] = frame_ptr[cFrame*x + 2];
            store_ptr[cStore*x + 3] = hit_ptr[x];
        }
    }

    while (nFrame >= vectorMulti.size()) {
        vectorMulti.append(0);
    }

    if (vectorMulti.at(nFrame)) {
        delete vectorMulti[nFrame];
    }
    vectorMulti[nFrame] = new Image(frame);

    //QString file = QString("g:/memorize/%1/frame-%2.png").arg(nQueue).arg(nFrame);
    //store->save(file);
    //delete store;
}

Image *Memorize::loadFrame(int nQueue, int nFrame)
{
    Q_ASSERT(nFrame < vectorMulti.size());
    Q_ASSERT(vectorMulti.at(nFrame));

    return vectorMulti[nFrame];

    //QString file = QString("g:/memorize/%1/frame-%2.png").arg(nQueue).arg(nFrame);
    //return new Image(file);
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
    Q_ASSERT(alpha->channels() >= 3);
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

void Memorize::mulHit(Image *hit, Image *alpha)
{
    Q_ASSERT(alpha->channels() >= 3);
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

void Memorize::stepQueueMultiRecord(Image *frame)
{
    Image *hit = process(0)->hit();

    if (mRecord.isPlay) {
        if (mRecord.play >= mRecord.count) {
            mRecord.play = 0;
            if (mRecord.repeats > 0) {
                mRecord.repeats--;
            }
            else if (mRecord.repeats == 0) {
                mRecord.isPlay = false;
            }
        }
    }

    if (mRecord.isPlay) {
        Image *store = loadFrame(0, mRecord.play);
        mergeFrames(frame, store);

        if (mRecord.isRecord) {
            mulHit(hit, store);
        }

        //delete store;
        mRecord.play++;
    }

    if (mRecord.isRecord) {
        saveFrame(0, mRecord.record, frame, hit);
        mRecord.record++;
        if (mRecord.count < mRecord.record) {
            mRecord.count = mRecord.record;
        }
    }
}

void Memorize::stepQueueRecord(Image *frame)
{
    for (int i=0; i<COUNT_RECORDS; i++) {
        int save = records.at(i).saveFrame;
        int play = records.at(i).playFrame;
        if (records.at(i).isRecord) {
            //addFrameToQueue(&records[i].queue, frame);
            saveFrame(i, save, frame, process(0)->hit());
            records[i].saveFrame += 1;
        }
        else if (records.at(i).repeats != 0) {
            if (play >= save) {
                records[i].playFrame = 0;
                if (records.at(i).repeats > 0)
                    records[i].repeats -= 1;
            }
            else {
                Image *store = loadFrame(i, play);
                mergeFrames(frame, store);
                delete store;
                records[i].playFrame++;
            }
        }
    }
}

#include "memorize.h"

Memorize::Memorize()
{
    control(queueManualLength=20, "Queue Length", 0, 999);
    button("Common", 1000, "Start Subtraction", 1001, "Stop Subtraction");

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
    w = process(0)->width();
    h = process(0)->height();
    Image *frame = process(0)->image();
    size(w, h);

    stepQueueManual(frame);
    stepQueueRecord(frame);

    frame->bind();
    color(1,1,1,1);
    image(frame, w/2, h/2, w, h);
    flush();
}

void Memorize::action(int id)
{
    if ( id == 1000 ) {
        process(0)->command("SubtractionImageStart");
    }
    if ( id == 1001 ) {
        process(0)->command("SubtractionImageStop");
    }
    else if (id < 1000) {
        int command = id % 10;
        int n = (id - command) / 10;
        qDebug() << id << n << command;
        if (command == 0) {
            while (records.at(n).queue.size()) {
                delete records[n].queue.dequeue();
            }
            records[n].isRecord = true;
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

uchar Memorize::blendValues(uchar c1, uchar c2)
{
    uint i1 = (uint)(c1);
    uint i2 = (uint)(c2);
    return (i1 + i2) / 2;
}

void Memorize::stepQueueManual(Image *frame)
{
    addFrameToQueue(&queueManual, frame);
    if (queueManual.size() < queueManualLength)
        addFrameToQueue(&queueManual, frame);

    if (queueManual.size() > queueManualLength) {
        delete queueManual.dequeue();
    }

    if (queueManual.size()) {
        Image *store = queueManual.dequeue();
        mergeFrames(frame, store);
        delete store;
    }
}

void Memorize::stepQueueRecord(Image *frame)
{
    for (int i=0; i<COUNT_RECORDS; i++) {
        if (records.at(i).isRecord) {
            addFrameToQueue(&records[i].queue, frame);
        }
        else if (records.at(i).repeats != 0) {
            int playFrame = records.at(i).playFrame;
            if (playFrame >= records.at(i).queue.size()) {
                records[i].playFrame = 0;
                if (records.at(i).repeats > 0)
                    records[i].repeats -= 1;
            }
            else {
                Image *store = records.at(i).queue.at(playFrame);
                mergeFrames(frame, store);
                records[i].playFrame++;
            }
        }
    }
}

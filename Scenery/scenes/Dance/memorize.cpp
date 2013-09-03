#include "memorize.h"

Memorize::Memorize()
{
    control(queueManualLength=20, "Queue Length", 0, 999);
    button("Test Buttons", 5, "b5", 8, "b8");
}

void Memorize::paint()
{
    w = process(0)->width();
    h = process(0)->height();
    Image *frame = process(0)->image();
    size(w, h);

    stepQueueManual(frame);

    frame->bind();
    color(1,1,1,1);
    image(frame, w/2, h/2, w, h);
    flush();
}

void Memorize::action(int id)
{
    qDebug() << id;
}

void Memorize::addFrameToQueue(QQueue<Image *> queue, Image *frame)
{
    Q_ASSERT(frame->channels() == 3);
    Image *store = new Image(w, h, 4);
    for( int y=0; y<h; y++ ) {
        uchar*   hit_ptr = (uchar*) (process(0)->hit()->data() + y * process(0)->hit()->step());
        uchar* frame_ptr = (uchar*) (frame->data() + y * frame->step());
        uchar* store_ptr = (uchar*) (store->data() + y * store->step());
        for( int x=0; x<w; x++ ) {
            store_ptr[store->channels()*x + 0] = frame_ptr[frame->channels()*x + 0];
            store_ptr[store->channels()*x + 1] = frame_ptr[frame->channels()*x + 1];
            store_ptr[store->channels()*x + 2] = frame_ptr[frame->channels()*x + 2];
            store_ptr[store->channels()*x + 3] = hit_ptr[x];
        }
    }

    queueManual.enqueue(store);
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
            if (alpha_ptr[cAlpha*x + 3] && !hit_ptr[x]) {
                if (!hit_ptr[x]) {
                    frame_ptr[cFrame*x + 0] = alpha_ptr[cAlpha*x + 0];
                    frame_ptr[cFrame*x + 1] = alpha_ptr[cAlpha*x + 1];
                    frame_ptr[cFrame*x + 2] = alpha_ptr[cAlpha*x + 2];
                }
                else {
                    frame_ptr[cFrame*x + 0] = blendValues(frame_ptr[cFrame*x + 0], alpha_ptr[cAlpha*x + 0]);
                    frame_ptr[cFrame*x + 1] = blendValues(frame_ptr[cFrame*x + 1], alpha_ptr[cAlpha*x + 1]);
                    frame_ptr[cFrame*x + 2] = blendValues(frame_ptr[cFrame*x + 2], alpha_ptr[cAlpha*x + 2]);
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
    addFrameToQueue(queueManual, frame);
    if (queueManual.size() < queueManualLength)
        addFrameToQueue(queueManual, frame);

    if (queueManual.size() > queueManualLength) {
        delete queueManual.dequeue();
    }

    //qDebug() << "!!";

    if (queueManual.size()) {
        Image *store = queueManual.dequeue();
        mergeFrames(frame, store);
        delete store;
    }

/*
    queueManual.enqueue(new Image(frame));
    if (queueManual.size() < queueManualLength)
        queueManual.enqueue(new Image(frame));

    if (queueManual.size() > queueManualLength) {
        delete queueManual.dequeue();
    }
*/

/*
    if (queueManual.size()) {
        Image *store = queueManual.dequeue();
        uchar* frame_ptr = (uchar*) (frame->data());
        uchar* store_ptr = (uchar*) (store->data());
        for (int i=0; i<frame->size(); i++) {
            uint i1 = (uint)(frame_ptr[i]);
            uint i2 = (uint)(store_ptr[i]);
            frame->data()[i] = (i1 + i2) / 2;
        }
        delete store;
    }
*/
}

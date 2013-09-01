#include "memorize.h"

Memorize::Memorize()
{
    control(stackLength=20, "Stack Length", 0, 100);
}

void Memorize::paint()
{
    int width = process(0)->width();
    int height = process(0)->height();
    size(width, height);

    if (queue.size() > stackLength) {
        delete queue.dequeue();
    }

    Image *newImage = new Image(process(0)->image());
    queue.enqueue(newImage);

    Image *videoImage = process(0)->image();

    if (queue.size() == stackLength + 1) {
        Image *headImage = queue.head();
        for (int i=0; i<videoImage->size(); i++) {
            char c1 = videoImage->data()[i];
            char c2 = headImage->data()[i];


            unsigned char uc1 = reinterpret_cast<unsigned char&>(c1);
            unsigned char uc2 = reinterpret_cast<unsigned char&>(c2);

            uint i1 = (uint)(uc1) + 128;
            uint i2 = (uint)(uc2) + 128;

            uint p = (i1 + i2) / 2 - 128;

            //char r = (char)(p);
            char r = reinterpret_cast<char&>(p);

            if ( p > 255 || p < 0) {
                //qDebug() << r;
            }

            videoImage->data()[i] = r;
        }
    }

    videoImage->bind();
    color(1,1,1,1);
    image(process(0)->image(), width/2, height/2, width, height);
    flush();
}

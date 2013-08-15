#include "shift.h"

Shift::Shift()
{
}

void Shift::setup()
{
    width = process(0)->width();
    height = process(0)->height();
    imageShift = new Image(width, height, 3);
    for (int i=0; i<imageShift->size(); i++)
        imageShift->data()[i] = random(255);
}

void Shift::resize()
{
    background(0, 0, 0, 1);
}

void Shift::paint()
{
    size(width, height);

    Image *imageStream = process(0)->image();
    char *dShift  = imageShift->data();
    char *dStream = imageStream->data();

    for (int j=0; j<imageShift->height(); j++) {
        for (int i=1; i<imageShift->width(); i++) {
            int c = imageShift->channels();
            int s = j * imageShift->width() * c;
            dShift[s+(i-1)*c + 0] = dShift[s+i*c + 0];
            dShift[s+(i-1)*c + 1] = dShift[s+i*c + 1];
            dShift[s+(i-1)*c + 2] = dShift[s+i*c + 2];
        }
    }

    for (int j=0; j<height; j++) {
        int c = imageShift->channels();
        int s = j * width * c;
        int imax = width-1;
        int icenter = width/2;

        dShift[s+imax*c + 0] = dStream[s+icenter*c + 0];
        dShift[s+imax*c + 1] = dStream[s+icenter*c + 1];
        dShift[s+imax*c + 2] = dStream[s+icenter*c + 2];
    }

    imageShift->bind();
    color(1,1,1,1);
    image(imageShift, width/2, height/2, width, height);

}

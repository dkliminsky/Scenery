#include "drawing.h"

Drawing::Drawing()
{
}

void Drawing::setup()
{
    background(0.0f, 0.0f, 0.0f, 1.0f);
    lineImage = loadImage("images/line5.png");
}

void Drawing::paint()
{
    size(getWidth(0), getHeight(0));
    color(1,0,0);
    lineWidth(15);

    SeqAreas &seqAreas = getSeqAreas(0);
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        if (seqArea.number > 1) {
            line(lineImage, seqArea.ptPrev[0], seqArea.ptPrev[1], seqArea.pt[0], seqArea.pt[1]);
        }
    }

}

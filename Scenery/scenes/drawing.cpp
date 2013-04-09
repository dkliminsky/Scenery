#include "drawing.h"

Drawing::Drawing()
{
    control(backColor=Color(0,0,0,0), "Background");
    control(lineColor=Color(1,0,0,1), "Line Color");
    control(lineSize=10, "Line size", 0, 200);
    control(clearSize=10, "Line size", 0, 200);
    control(isClear=false, "Clear");

    lineImage = loadImage("images/line2.png");
}

void Drawing::setup()
{
    size(getWidth(0), getHeight(0));
    background(0.0f, 0.0f, 0.0f, 1.0f);
}

void Drawing::paint()
{
    background(backColor);
    color(lineColor);

    if (isClear) {
        lineWidth(clearSize);
        color(0,0,0,1);
    }
    else {
        lineWidth(lineSize);
        color(lineColor);
    }

    SeqAreas &seqAreas = getSeqAreas(0);
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        if (seqArea.number > 1) {
            line(lineImage, seqArea.ptPrev[0], seqArea.ptPrev[1], seqArea.pt[0], seqArea.pt[1]);
        }
    }

}

#include "brush.h"

Brush::Brush()
{
    control(speedLimit=30, "Speed limit", 0, 100);
    control(strokeWidth=120, "Stroke Width", 0, 300);
}

void Brush::setup()
{
    imgStroke = loadImage("images/stroke02.png");
    imgLine   = loadImage("images/line2.png");
}

void Brush::paint()
{
    size(getWidth(0), getHeight(0));
    background(0.0f, 0.0f, 0.0f, 1.0f);

    SeqAreas &seqAreas = getSeqAreas(0);
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        if (seqArea.number > 1 && seqArea.length > speedLimit) {
            Stroke stroke;
            stroke.pt.x = seqArea.pt[0] - (seqArea.pt[0] - seqArea.ptPrev[0])/2.0;
            stroke.pt.y = seqArea.pt[1] - (seqArea.pt[1] - seqArea.ptPrev[1])/2.0;
            stroke.width = seqArea.length;
            stroke.height = strokeWidth;
            stroke.angle = seqArea.angle;
            stroke.color = Color(1, 0, 0);
            strokes.append(stroke);

            if (strokes.size() > 2000)
                strokes.pop_front();

        }
    }

    color(1,1,1,1);
    image(imgStroke, 25, 25, 70+10, 150, -M_PI/4.0);
    image(imgStroke, 75, 50, 50+10, 150, 0);
    image(imgStroke, 100, 75, 50+10, 150, -M_PI/2.0);
    image(imgStroke, 125, 75, 70+10, 150, M_PI/4.0);

    line(imgLine, 300, 300, 400, 400);

    for (int i=0; i<strokes.size(); i++) {
        const Stroke &stroke = strokes.at(i);
        color(stroke.color);
        //line(imgStroke, stroke.pt.x, stroke.pt.y, stroke.width, stroke.height);
        image(imgStroke, stroke.pt.x, stroke.pt.y,
              stroke.width, stroke.height, stroke.angle);
    }

}

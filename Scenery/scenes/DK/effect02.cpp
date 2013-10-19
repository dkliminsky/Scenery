#include "effect02.h"

Effect02::Effect02()
{
    control(&imageCircle, "Circle image", "images/forms/", "circle01.png");
    control(&imageCircle2, "Circle image 2", "images/forms/", "circle02.png");

    control(backColor=Color(0,0,0,1), "Background");
    control(circleColor[0]=Color(1,0,0,1), "Circle color");
    control(circleColor[1]=Color(0,1,0,1), "Circle color");
    control(circleColor[2]=Color(1,1,0,1), "Circle color");
    control(circleColor[3]=Color(0,0,1,1), "Circle color");
    control(circleColor[4]=Color(1,0,1,1), "Circle color");
    control(circleColor[5]=Color(0,1,1,1), "Circle color");
    control(circleColor[6]=Color(1,1,1,1), "Circle color");

    control(circleDeviation=10, "circleDeviation", 1, 100);
    control(circleTimeLife=30, "circleTimeLife", 0, 100);
    control(circleTimeDisappear=30, "circleTimeDisappear", 0, 100);
    control(circleAlphaDisappear=0.05, "circleAlphaDisappear", 0, 1, 2);
    control(circleTimeGrow=10, "circleTimeGrow", 0, 100);
    control(circleGrowSize=2, "circleGrowSize", 0, 100);
}

void Effect02::setup()
{
    background(0, 0, 0);
}

void Effect02::paint()
{
    size(process(1)->width(), process(1)->height());
    background(backColor);

    SeqAreas &seqAreas = process(1)->seqAreas();
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        if (seqArea.number > 1 && seqArea.isUsed == false) {
            Circle circle;
            circle.x = seqArea.pt[0];
            circle.y = seqArea.pt[1];
            circle.angle = 0;
            circle.grow = circleTimeGrow;
            circle.ttl = circleTimeLife;
            circle.color = circleColor[random(7)];
            circles += circle;
        }
    }


    QList<Circle>::iterator i = circles.begin();
    while (i != circles.end()) {
        Circle &circle = *i;
        if (circle.ttl > 0) {
            circle.ttl--;

            if (circle.ttl < circleTimeDisappear) {
                circle.color.a-=circleAlphaDisappear;
                if (circle.color.a < 0)
                    circle.color.a = 0;
            }

            if (circle.grow > 0) {
                circle.grow--;
                circle.size += circleGrowSize;
            }

            //image(imageCircle, circle.x, circle.y, circle.size, circle.size);

            i++;
        }
        else {
            i = circles.erase(i);
        }
    }


    for (int n=0; n<3; n++){
        QList<Circle>::iterator i = circles.begin();
        while (i != circles.end()) {
            Circle &circle = *i;

            int x = circle.x + (random(circleDeviation) - circleDeviation/2);
            int y = circle.y + (random(circleDeviation) - circleDeviation/2);

            color(circle.color);
            image(imageCircle, x, y, circle.size/(n+1), circle.size/(n+1));

            i++;
        }
    }
}

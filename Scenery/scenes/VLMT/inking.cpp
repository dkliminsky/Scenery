#include "inking.h"

Inking::Inking()
{
}

void Inking::setup()
{

}

void Inking::paint()
{
    int width = process(0)->width();
    int height = process(0)->height();
    Contours &contours = process(0)->contours();

    size(width, height);
    background(0.0f, 0.0f, 0.0f, 1.0f);

    color(1,1,1);
    lineWidth(3);

    for (uint i=0; i<contours.size(); ++i) {
        Contour &contour = contours.at(i);
        ContourPt pt(0, 0);
        for (uint j=0; j<contour.size(); ++j )
        {
            line(pt.x, pt.y, contour.at(j).x, contour.at(j).y);
            pt.x = contour.at(j).x;
            pt.y = contour.at(j).y;
        }
    }
}

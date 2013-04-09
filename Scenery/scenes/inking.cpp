#include "inking.h"

Inking::Inking()
{
}

void Inking::setup()
{
    size(getWidth(0), getHeight(0));
}

void Inking::paint()
{
    Contours &contours = getContours(0);

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

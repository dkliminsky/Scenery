#include "inking.h"

Inking::Inking()
{
}

void Inking::setup()
{

}

void Inking::paint()
{
    int width = process(2)->width();
    int height = process(2)->height();
    Contours &contours = process(2)->contours();

    size(width, height);
    background(0.0f, 0.0f, 0.0f, 1.0f);

    color(1, 1, 1);
    lineWidth(1);

    for (uint i=0; i<contours.size(); ++i) {
        Contour &contour = contours.at(i);
        ContourPt pt(0, 0);
        bool isFirst = true;
        for (uint j=0; j<contour.size(); ++j )
        {
            if (isFirst) {
                isFirst = false;
            }
            else {
                line(pt.x, pt.y, contour.at(j).x, contour.at(j).y);
            }
            pt.x = contour.at(j).x;
            pt.y = contour.at(j).y;
        }
    }
}

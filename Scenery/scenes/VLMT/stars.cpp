#include "stars.h"

Stars::Stars()
{
    control(inkingLengthLimit=2, "Inking Lenght Limit", 0, 100);
    control(&imageStar, "Star Image", "images/flares/", "flare01.png");
    control(starProb=0.001, "starProb", 0, 1, 4);
    control(starTTL=1000, "starTTL", 0, 10000);
    control(starSize=5, "starSize", 0, 100);
    control(starSpeed=1, "starSpeed", -10, 10);
    control(starAcceleration=0.2, "starAcceleration", 0, 10, 3);
}

void Stars::setup()
{

}

void Stars::paint()
{
    int width = process(2)->width();
    int height = process(2)->height();
    Contours &contours = process(2)->contours();

    size(width, height);
    background(0.0f, 0.0f, 0.0f, 1.0f);

    color(1, 1, 1);

    int num = 0;
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
                double d = distance((double)(pt.x), (double)(pt.y), (double)(contour.at(j).x), (double)(contour.at(j).y));
                if (d > inkingLengthLimit) {
                    createStar((pt.x + contour.at(j).x)/2, (pt.y + contour.at(j).y)/2);
                    num++;
                }
            }
            pt.x = contour.at(j).x;
            pt.y = contour.at(j).y;
        }
    }

    QList<Star>::iterator i = stars.begin();
    while (i != stars.end()) {
        Star &star = *i;

        if ( star.ttl > 0) {
            star.ttl--;
            star.x += star.speed;
            star.speed = star.speed * starAcceleration;
            image(imageStar, star.x, star.y, star.size, star.size);
            i++;
        }
        else {
            i = stars.erase(i);
        }
    }


    text(30, 30, QString().number(num),  QFont("Times", 10));
}

void Stars::createStar(float x, float y)
{
    if ( chance(starProb) ) {
        Star star;
        star.x = x;
        star.y = y;
        star.size = starSize;
        star.speed = starSpeed;
        star.ttl = starTTL;
        stars.append(star);
    }
}

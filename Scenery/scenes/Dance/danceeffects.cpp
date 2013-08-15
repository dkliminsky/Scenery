#include "danceeffects.h"

DanceEffects::DanceEffects()
{
    control(&imageFlare, "Flare", "images/flares/", "flare01.png");

}

void DanceEffects::setup()
{

}

void DanceEffects::resize()
{

}

void DanceEffects::paint()
{
    int width = process(0)->width();
    int height = process(0)->height();

    size(width, height);
    process(0)->image()->bind();
    color(1,1,1,1);
    image(process(0)->image(), width/2, height/2, width, height);
    flush();

//    int x = 0;
//    int y = 0;
//    lineWidth(3);
//    Areas &areas = process(1)->areas();
//    for (unsigned int i=0; i<areas.size(); i++) {
//        Area &area = areas.at(i);

//        if (!(x == 0 && y == 0)) {
//            color(1, 0, 0, 0.7);
//            line(x, y, area.pt[0], area.pt[1]);
//        }
//        x = area.pt[0];
//        y = area.pt[1];
//    }


    Areas &areas = process(1)->areas();
    for (unsigned int i=0; i<areas.size(); i++) {
        Area &area = areas.at(i);
        image(imageFlare, area.pt[0], area.pt[1], 40, 40);
    }
}

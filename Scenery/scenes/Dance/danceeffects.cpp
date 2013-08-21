#include "danceeffects.h"

DanceEffects::DanceEffects()
{
    control(&imageFlare, "Flare", "images/flares/", "flare01.png");
    control(minDistance=50, "Min Distance");
    control(maxDistance=100, "Max Distance");

    control(nettingLineColor=Color(1,0,0,1), "Netting: Line color");
    control(nettingDecrease=0.1, "Netting: Decrease", 0, 1, 2);
    control(nettingLineWidth=3, "Netting: Line width", 1, 10);
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

    elementsArea.clear();
    Areas &areas = process(1)->areas();
    for (unsigned int i=0; i<areas.size(); i++) {
        Area &area = areas.at(i);
        ElementArea e;
        e.x = area.pt[0];
        e.y = area.pt[1];
        e.used = false;
        elementsArea += e;

        //image(imageFlare, area.pt[0], area.pt[1], 40, 40);
    }

    for(int i=0; i<elementsArea.size(); i++) {

        for (int j=0; j<5; j++) {
            int r = random(elementsArea.size());
            float d = distance(elementsArea.at(i).x, elementsArea.at(i).y,
                               elementsArea.at(r).x, elementsArea.at(r).y);

            if (r!=i && elementsArea.at(r).used==false &&
                elementsArea.at(i).used==false &&
                d > minDistance && d < maxDistance) {
                elementsArea[i].used = true;
                elementsArea[r].used = true;

                float x1 = elementsArea.at(i).x;
                float y1 = elementsArea.at(i).y;
                float x2 = elementsArea.at(r).x;
                float y2 = elementsArea.at(r).y;

                ElementDraw e;
                e.type = random(3) + 1;
                e.color = nettingLineColor;
                e.x1 = x1;
                e.y1 = y1;
                e.x2 = x2;
                e.y2 = y2;
                elementsDraw += e;

            }
        }
    }


    QMutableVectorIterator<ElementDraw> i(elementsDraw);
    while (i.hasNext()) {
        ElementDraw &e = i.next();

        int type = e.type;
        float x1 = e.x1;
        float y1 = e.y1;
        float x2 = e.x2;
        float y2 = e.y2;
        float d = distance(x1, y1, x2, y2);

        color(e.color);

        if (type == 1) {
            lineWidth(nettingLineWidth);
            line(x1, y1, x2, y2);
        }
        else if ( type == 2) {
            float a = angle(x1, y1, x2, y2);
            float x3 = (x1 + (x2 - x1) / 2) + d/4 * sin(a + pi() / 4);
            float y3 = (y1 + (y2 - y1) / 2) + d/4 * cos(a + pi() / 4);
            float x4 = (x1 + (x2 - x1) / 2) - d/4 * sin(a + pi() / 4);
            float y4 = (y1 + (y2 - y1) / 2) - d/4 * cos(a + pi() / 4);

            lineWidth(nettingLineWidth);
            line(x1, y1, x3, y3);
            line(x3, y3, x4, y4);
            line(x4, y4, x2, y2);
        }
        else if ( type == 3) {
            float a = angle(x1, y1, x2, y2);
            float x3 = (x1 + (x2 - x1) / 2) + d/4 * sin(a + pi() / 4);
            float y3 = (y1 + (y2 - y1) / 2) + d/4 * cos(a + pi() / 4);
            float x4 = (x1 + (x2 - x1) / 2) - d/4 * sin(a + pi() / 4);
            float y4 = (y1 + (y2 - y1) / 2) - d/4 * cos(a + pi() / 4);

            lineWidth(nettingLineWidth);
            lineParts(10);
            bezier(x1, y1, x3, y3, x4, y4, x2, y2);
        }


        e.color.a -= nettingDecrease;
        if (e.color.a <= 0) {
            i.remove();
        }
    }
}

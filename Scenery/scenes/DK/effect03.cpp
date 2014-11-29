#include "effect03.h"


Effect03::Effect03()
{
    control(scaleX=1, "Scale X", 1, 5, 1);
    control(scaleY=1, "Scale Y", 1, 5, 1);
    control(backColor=Color(0,0,0,1), "Background");

    control(decrease=0.1, "Decrease elements", 0, 1, 2);

    control(&imageFlare, "Flare: Image", "images/flares/", "flare02.png");
    control(flareColor=Color(1,0,0,1), "Flare: Color");
    control(flareSize=0, "Flare: Size", 0, 100);

    control(nettingLineColor=Color(1,0,0,1), "Netting: Line color");
    control(nettingLineWidth=0, "Netting: Line width", 0, 10);
    control(nettingMinDistance=50, "Netting: Min Distance");
    control(nettingMaxDistance=100, "Netting: Max Distance");

    control(contourLineColor=Color(1,1,1,1), "Contour: Line color");
    control(contourLineWidth=0, "Contour: Line width", 0, 10);
}

void Effect03::setup()
{

}

void Effect03::resize()
{

}

void Effect03::paint()
{
    int width = process(0)->width();
    int height = process(0)->height();

    size(width, height);
    background(backColor);

    //process(0)->image()->bind();
    //color(1,1,1,1);
    //image(process(0)->image(), width/2, height/2, width, height);
    //flush();

    effectFlare();
    effectContour();
    effectNetting();
    drawElements();
}

void Effect03::effectFlare()
{
    if (flareSize > 0) {
        Areas &areas = process(0)->areas();
        //color(flareColor);
        for (unsigned int i=0; i<areas.size(); i++) {
            Area &area = areas.at(i);
            //image(imageFlare, area.pt[0], area.pt[1], flareSize, flareSize);

            ElementDraw e;
            e.type = 0;
            e.image = imageFlare;
            e.width = flareSize;
            e.color = flareColor;
            e.x1 = area.pt[0] + random(20) - 20;
            e.y1 = area.pt[1] + random(20) - 20;;
            elementsDraw += e;

        }
    }
}

void Effect03::effectNetting()
{
    if (nettingLineWidth > 0) {

        nettingsArea.clear();

        Areas &areas = process(0)->areas();
        for (unsigned int i=0; i<areas.size(); i++) {
            Area &area = areas.at(i);
            NettingArea e;
            e.x = area.pt[0];
            e.y = area.pt[1];
            e.used = false;
            nettingsArea += e;
        }

        for(int i=0; i<nettingsArea.size(); i++) {
            for (int j=0; j<5; j++) {
                int r = random(nettingsArea.size());
                float d = distance(nettingsArea.at(i).x, nettingsArea.at(i).y,
                                   nettingsArea.at(r).x, nettingsArea.at(r).y);

                if (r!=i && nettingsArea.at(r).used==false &&
                    nettingsArea.at(i).used==false &&
                    d > nettingMinDistance && d < nettingMaxDistance) {
                    nettingsArea[i].used = true;
                    nettingsArea[r].used = true;

                    float x1 = nettingsArea.at(i).x;
                    float y1 = nettingsArea.at(i).y;
                    float x2 = nettingsArea.at(r).x;
                    float y2 = nettingsArea.at(r).y;

                    ElementDraw e;
                    e.type = random(3) + 1;
                    e.width = nettingLineWidth;
                    e.color = nettingLineColor;
                    e.x1 = x1;
                    e.y1 = y1;
                    e.x2 = x2;
                    e.y2 = y2;
                    elementsDraw += e;
                }
            }
        }
    }
}

void Effect03::effectContour()
{
    if (contourLineWidth > 0) {
        Contours &contours = process(0)->contours();
        color(contourLineColor);
        lineWidth(contourLineWidth);
        int nContours = 0;

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
                    //line(pt.x, pt.y, contour.at(j).x, contour.at(j).y);

                    ElementDraw e;
                    e.type = 1;
                    e.width = contourLineWidth;
                    e.color = contourLineColor;
                    e.x1 = pt.x;
                    e.y1 = pt.y;
                    e.x2 = contour.at(j).x;
                    e.y2 = contour.at(j).y;
                    elementsDraw += e;

                }
                pt.x = contour.at(j).x;
                pt.y = contour.at(j).y;

                nContours++;
            }
        }

        color(1, 1, 1, 1);
        text(30, 30, QString("Contours: %1").arg(nContours));
    }
}

void Effect03::drawElements()
{
    int w = process(0)->width();
    int h = process(0)->height();

    QMutableListIterator<ElementDraw> i(elementsDraw);
    while (i.hasNext()) {
        ElementDraw &e = i.next();

        int type = e.type;
        float x1 = e.x1;
        float y1 = e.y1;
        float x2 = e.x2;
        float y2 = e.y2;
        int width = e.width;
        float d = distance(x1, y1, x2, y2);

        color(e.color);

        if (type == 0) {
            image(e.image,
                  x1*scaleX - (w*scaleX - w)/2,
                  y1*scaleY - (h*scaleY - h)/2,
                  width, width);
        }
        else if (type == 1) {
            lineWidth(e.width);
            line(x1*scaleX - (w*scaleX - w)/2,
                 y1*scaleY - (h*scaleY - h)/2,
                 x2*scaleX - (w*scaleX - w)/2,
                 y2*scaleY - (h*scaleY - h)/2);
        }
        else if ( type == 2) {
            float a = angle(x1, y1, x2, y2);
            float x3 = (x1 + (x2 - x1) / 2) + d/4 * sin(a + pi() / 4);
            float y3 = (y1 + (y2 - y1) / 2) + d/4 * cos(a + pi() / 4);
            float x4 = (x1 + (x2 - x1) / 2) - d/4 * sin(a + pi() / 4);
            float y4 = (y1 + (y2 - y1) / 2) - d/4 * cos(a + pi() / 4);

            lineWidth(e.width);
            line(x1*scaleX - (w*scaleX - w)/2,
                 y1*scaleY - (h*scaleY - h)/2,
                 x3*scaleX - (w*scaleX - w)/2,
                 y3*scaleY - (h*scaleY - h)/2);
            line(x3*scaleX - (w*scaleX - w)/2,
                 y3*scaleY - (h*scaleY - h)/2,
                 x4*scaleX - (w*scaleX - w)/2,
                 y4*scaleY - (h*scaleY - h)/2);
            line(x4*scaleX - (w*scaleX - w)/2,
                 y4*scaleY - (h*scaleY - h)/2,
                 x2*scaleX - (w*scaleX - w)/2,
                 y2*scaleY - (h*scaleY - h)/2);
        }
        else if ( type == 3) {
            float a = angle(x1, y1, x2, y2);
            float x3 = (x1 + (x2 - x1) / 2) + d/4 * sin(a + pi() / 4);
            float y3 = (y1 + (y2 - y1) / 2) + d/4 * cos(a + pi() / 4);
            float x4 = (x1 + (x2 - x1) / 2) - d/4 * sin(a + pi() / 4);
            float y4 = (y1 + (y2 - y1) / 2) - d/4 * cos(a + pi() / 4);

            lineWidth(e.width);
            lineParts(10);
            bezier(x1*scaleX - (w*scaleX - w)/2,
                   y1*scaleY - (h*scaleY - h)/2,
                   x3*scaleX - (w*scaleX - w)/2,
                   y3*scaleY - (h*scaleY - h)/2,
                   x4*scaleX - (w*scaleX - w)/2,
                   y4*scaleY - (h*scaleY - h)/2,
                   x2*scaleX - (w*scaleX - w)/2,
                   y2*scaleY - (h*scaleY - h)/2);
        }

        e.color.a -= decrease;
        if (e.color.a <= 0) {
            i.remove();
        }
    }

    color(1, 1, 1, 1);
    //text(30, 20, QString("Elements: %1").arg(elementsDraw.size()));
}

#include "cage.h"
#include <QDebug>

Cage::Cage()
{
    m.resize(MATRIX_SIZE);
    for (int j=0; j<MATRIX_SIZE; j++) {
        m[j].resize(MATRIX_SIZE);
        for (int i=0; i<MATRIX_SIZE; i++)
        {
            m[j][i] = 0;
        }
    }
    cxPrev = 0;
    cyPrev = 0;
    isCenterPrev = false;

    control(backColor=Color(1,1,1,1), "Background");
    control(boxColor,  "Box");
    control(cellSize=10, "Cell size", 2, 50);
    control(boxSize=20, "Box size", 1, 50);
    control(boxDeviation=10, "Box deviation", 1, 50);
    control(influence=0, "Influence", 0, 10);
    control(prob=0.02, "Prob", 0, 1, 2);
}

void Cage::setup()
{
    box = loadImage("images/box.png");
}

void Cage::paint()
{
    int &width = getWidth(0);
    int &height = getHeight(0);

    int maxX = width/cellSize+1;
    int maxY = height/cellSize+1;

    if (maxX >= MATRIX_SIZE || maxY >= MATRIX_SIZE)
        return;

    size(width, height);
    background(backColor);
    color(boxColor);

    int cx = 0;
    int cy = 0;
    bool isCenter = false;
    Areas &areas = getAreas(0);
    if (areas.size()>0) {
        cx = areas.at(0).pt[0];
        cy = areas.at(0).pt[1];
        isCenter = true;
    }

    for (unsigned int i=0; i<areas.size(); i++) {
        Area &area = areas.at(i);

        if (area.pt[0] > 0 && area.pt[1] > 0 && area.pt[0] < width && area.pt[1] < height) {
            int x1 = (area.pt[0]-(area.width/2 ))/cellSize - influence;
            int y1 = (area.pt[1]-(area.height/2))/cellSize - influence;

            int x2 = (area.pt[0]+(area.width/2 ))/cellSize + influence;
            int y2 = (area.pt[1]+(area.height/2))/cellSize + influence;

            for (int x=x1; x<=x2; x++)
               for (int y=y1; y<=y2; y++) {
                    if (x>=0 && x<MATRIX_SIZE && y>=0 && y<MATRIX_SIZE)
                    m[x][y] = 0;
               }

        }

        cx = (cx + area.pt[0])/2;
        cy = (cy + area.pt[1])/2;
    }

    m[0][0] = 1;
    m[maxX-1][0] = 1;
    for (int i=0; i<maxX; i++)
        for (int j=0; j<maxY; j++)
        {
            if ( i > 0 && m[i-1][j] == 1 && chance(prob) ) {
                m[i][j] = 1;
            }
            if ( j > 0 && m[i][j-1] == 1 && chance(prob) ) {
                m[i][j] = 1;
            }
            if ( i < maxX-1 && m[i+1][j] == 1 && chance(prob) ) {
                m[i][j] = 1;
            }
            if ( j < maxY-1 && m[i][j+1] == 1 && chance(prob) ) {
                m[i][j] = 1;
            }

            if ( m[i][j] == 1) {
                image(box, i*cellSize+random(boxDeviation)-boxDeviation/2,
                           j*cellSize+random(boxDeviation)-boxDeviation/2, boxSize, boxSize);
            }
        }

    if (isCenter) {
        if (isCenterPrev) {
            color(1,0,0,1);
            lineWidth(10);
            line(cxPrev, cyPrev, cx, cy);
        }
        isCenterPrev = true;
    }
    else {
        isCenterPrev = false;
    }
    cxPrev = cx;
    cyPrev = cy;
}



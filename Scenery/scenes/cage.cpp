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
    control(prob=10, "Prob", 0, 100);
    control(isWave=false, "Wave");
    control(waveWidth=20, "Wave width", 1, 200);
    control(waveForce=10, "Wave force", 1, 50);
    control(waveSpeed=7,  "Wave speed", 1, 50);
    control(isWaveDebug=false, "Wave Debug");
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

    applyWave();
    Areas &areas = getAreas(0);
    for (unsigned int i=0; i<areas.size(); i++) {
        Area &area = areas.at(i);

        if (area.pt[0] > 0 && area.pt[1] > 0 && area.pt[0] < width && area.pt[1] < height) {
            int x1 = (area.pt[0]-(area.width/2 ))/cellSize - influence;
            int y1 = (area.pt[1]-(area.height/2))/cellSize - influence;

            int x2 = (area.pt[0]+(area.width/2 ))/cellSize + influence;
            int y2 = (area.pt[1]+(area.height/2))/cellSize + influence;

            zeroMatrix(x1, y1, x2, y2);
        }
    }

    m[0][0] = 1;
    m[maxX-1][0] = 1;
    color(boxColor);
    for (int i=0; i<maxX; i++)
        for (int j=0; j<maxY; j++)
        {
            if ( i > 0 && m[i-1][j] == 1 && chance(prob/500.0) ) {
                m[i][j] = 1;
            }
            if ( j > 0 && m[i][j-1] == 1 && chance(prob/500.0) ) {
                m[i][j] = 1;
            }
            if ( i < maxX-1 && m[i+1][j] == 1 && chance(prob/500.0) ) {
                m[i][j] = 1;
            }
            if ( j < maxY-1 && m[i][j+1] == 1 && chance(prob/500.0) ) {
                m[i][j] = 1;
            }

            if ( m[i][j] == 1) {
                image(box, i*cellSize+random(boxDeviation)-boxDeviation/2,
                           j*cellSize+random(boxDeviation)-boxDeviation/2, boxSize, boxSize);
            }
        }
}

void Cage::zeroMatrix(int x1, int y1, int x2, int y2)
{
    for (int x=x1; x<=x2; x++)
       for (int y=y1; y<=y2; y++) {
            if (x>=0 && x<MATRIX_SIZE && y>=0 && y<MATRIX_SIZE)
            m[x][y] = 0;
       }
}

void Cage::applyWave()
{
    bool isCenter = false;
    float cx = 0;
    float cy = 0;
    Areas &areas = getAreas(0);
    if (areas.size()>0) {
        cx = areas.at(0).pt[0];
        cy = areas.at(0).pt[1];
        isCenter = true;
    }

    for (unsigned int i=0; i<areas.size(); i++) {
        Area &area = areas.at(i);
        cx = (cx + area.pt[0])/2.0;
        cy = (cy + area.pt[1])/2.0;
    }

    if (isCenter) {
        if (isCenterPrev) {
            if (isWaveDebug) {
                color(1,0,0);
                lineWidth(10);
                line(cxPrev, cyPrev, cx, cy);
            }

            if (isWave) {
                Wave wave;
                wave.x = cx;
                wave.y = cy;
                wave.angle = angle(cxPrev, cyPrev, cx, cy);
                wave.lenght = distance(cxPrev, cyPrev, cx, cy)*waveForce;
                waves.append(wave);
            }
        }
        isCenterPrev = true;
    }
    else {
        isCenterPrev = false;
    }
    cxPrev = cx;
    cyPrev = cy;
    QList<Wave>::iterator i= waves.begin();
    while (i != waves.end()) {
        Wave &wave = *i;
        if (wave.lenght > 0) {
            wave.lenght -= waveSpeed;
            wave.x += waveSpeed*cos(wave.angle);
            wave.y += waveSpeed*sin(wave.angle);

            if (isWave) {
                int x1 = (wave.x - waveWidth/2.0)/cellSize;
                int y1 = (wave.y - waveWidth/2.0)/cellSize;

                int x2 = (wave.x + waveWidth/2.0)/cellSize;
                int y2 = (wave.y + waveWidth/2.0)/cellSize;

                zeroMatrix(x1, y1, x2, y2);
            }

            i++;
        }
        else {
            i = waves.erase(i);
        }
    }

}



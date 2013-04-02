#include "strings.h"

Strings::Strings()
{
    control(backColor=Color(0,0,0,0.2), "Background");
    control(color1=Color(1,1,1,0.5), "Color 1");
    control(color2=Color(1,1,1,1), "Color 2");
    control(height1=8.0, "Width 1", 0.0, 10.0, 1);
    control(height2=2.0, "Width 2", 0.0, 10.0, 1);
    control(count=1, "Count strings", 0, 100);
    control(frequency=100, "Frequency/100", 0, 500);
    control(Amax=50, "Amplitude max", 0, 200);
    control(force=1.0, "Force", 0, 50, 1);
    control(damping=0.1, "Damping", 0, 10, 1);
    control(isSag=false, "Sag");
    control(isShadow=false, "Shadow");
    control(isDebug=false, "Debug");
    control(state="Debug", "State", QStringList() << "Default" << "Test");
}

void Strings::setup()
{
    lineImage = loadImage("images/line5.png");
}

void Strings::paint()
{
    int &width = getWidth(0);
    int &height = getHeight(0);    
    float cell = (float)width / count;
    float w = 2.0*M_PI*frequency/100.0;

    size(width, height);
    background(backColor);

    if (strings.count() < count) {
        int prevCount = strings.count();
        strings.resize(count);
        for (int i=prevCount; i<strings.count(); i++) {
            strings[i].a = 0;
            strings[i].dx = 0;
            strings[i].dxPrev = strings[i].dx;
            strings[i].direction = 1;
            strings[i].y2 = height/2.0;
            strings[i].y3 = height/2.0;
        }
    }

    for(int i=0; i<strings.count(); i++) {
        float x = cell * i + cell/2.0;
        float yMin = height;
        float yMax = 0;
        float yAverage = height/2;
        bool isFirstAverage = true;

        SeqAreas &seqAreas = getSeqAreas(0);
        for (unsigned int j=0; j<seqAreas.size(); j++) {
            SeqArea &seqArea = seqAreas.at(j);
            if (seqArea.number > 1) {
                bool isFound = false;

                // Влияние на струну слева на право
                if ( seqArea.ptPrev[0] < x && seqArea.pt[0] > x) {
                    strings[i].dx += force;
                    // Если совпадает движение с влиянием, увеличиваем амплитуду,
                    // иначе уменьшаем
                    if (strings[i].direction == 1)
                        strings[i].a += force;
                    else
                        strings[i].a -= force;
                    isFound = true;
                }
                // Влияние справа на лево
                else if ( seqArea.pt[0] < x && seqArea.ptPrev[0] > x) {
                    strings[i].dx -= force;
                    // Если совпадает движение с влиянием, увеличиваем амплитуду,
                    // иначе уменьшаем
                    if (strings[i].direction == -1)
                        strings[i].a += force;
                    else
                        strings[i].a -= force;
                    isFound = true;
                }

                if (isFound) {
                    if (seqArea.pt[1] > yMax && seqArea.pt[1] < height)
                        yMax = seqArea.pt[1];
                    if (seqArea.pt[1] < yMin && seqArea.pt[1] > 0)
                        yMin = seqArea.pt[1];

                    if (isFirstAverage) {
                        yAverage = seqArea.pt[1];
                        isFirstAverage = false;
                    }
                    else {
                        yAverage = yAverage + (seqArea.pt[1] - yAverage)/2.0;
                    }

                    if (isDebug) {
                        color(1,0,0);
                        line (seqArea.ptPrev[0], seqArea.ptPrev[1], seqArea.pt[0], seqArea.pt[1]);
                    }
                }
            }
        }

        // Меняем амплитуду, в зависимости от текущей раскачки струны и
        // ограничиваем смещение струны максимальной амплитудой
        if (strings[i].dx<0) {
            if (-strings[i].dx>Amax)
                strings[i].dx = -Amax;
            if (-strings[i].dx>strings[i].a)
                strings[i].a = -strings[i].dx;
        }
        else {
            if (strings[i].dx>Amax)
                strings[i].dx = Amax;
            if (strings[i].dx>strings[i].a)
                strings[i].a = strings[i].dx;
        }
        if ( strings[i].a > Amax)
            strings[i].a = Amax;

        // Вычисляем время, в которое струна будет в этом положении
        float t = 0;
        if (strings[i].a>0)
            t = (asin(strings[i].dx/strings[i].a)*1000.0)/(w);

        //
        t += dtime()*strings[i].direction;

        // Линейное затухание струны
        strings[i].a -= damping;
        if (strings[i].a<0)
            strings[i].a = 0.0;

        strings[i].dxPrev = strings[i].dx;
        strings[i].dx = strings[i].a*sin(w*t/1000.0);

        // Определяем направление движения
        if ( strings[i].direction == 1 &&strings[i].dx - strings[i].dxPrev < 0 ) {
            strings[i].direction = -1;
        }
        else if ( strings[i].direction == -1 &&strings[i].dx - strings[i].dxPrev > 0 ) {
            strings[i].direction = 1;
        }

        float y2 = strings[i].y2;
        if (isFirstAverage) {
            if (y2 < yAverage)
                y2 += 1;
            else if (y2 > yAverage)
                y2 -= 1;
        }
        else if (isSag) {
            if (y2 < yAverage)
                y2 += 5;
            else if (y2 > yAverage)
                y2 -= 5;
        }

        strings[i].x1 = x;
        strings[i].y1 = 0;
        strings[i].x2 = x + strings[i].dx;
        strings[i].y2 = y2;
        strings[i].x3 = strings[i].x2;
        strings[i].y3 = strings[i].y2;
        strings[i].x4 = x;
        strings[i].y4 = height;

        strings[i].x1s = strings[i].x1;
        strings[i].y1s = strings[i].y1;
        strings[i].x2s = x + strings[i].dx*0.5;
        strings[i].y2s = strings[i].y2;
        strings[i].x3s = strings[i].x2s;
        strings[i].y3s = strings[i].y3;
        strings[i].x4s = strings[i].x4;
        strings[i].y4s = strings[i].y4;
    }

    color(color1);
    lineWidth(height1);
    for(int i=0; i<strings.count(); i++) {
        const String &s = strings.at(i);
        bezier(lineImage, s.x1, s.y1, s.x2, s.y2, s.x3, s.y3, s.x4, s.y4);
    }

    if (isShadow) {
        color(color2);
        lineWidth(height2);
        for(int i=0; i<strings.count(); i++) {
            const String &s = strings.at(i);
            bezier(lineImage, s.x1s, s.y1s, s.x2s, s.y2s, s.x3s, s.y3s, s.x4s, s.y4s);
        }
    }
}

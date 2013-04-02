#ifndef PROCESSDATA_H
#define PROCESSDATA_H

#include <vector>
#include <list>
#include <deque>

using std::vector;
using std::list;
using std::deque;

struct Area {
    int pt[2];
    int ptReal[2];
    int width;
    int height;
    int widthReal;
    int heightReal;
};

struct SeqArea {
    // Номер последовательности
    // 0 - последовательность не найдена,
    // и все данные не действительны
    unsigned int number;

    // Признак, что точки для этой линии нет и
    // все данные в этом элементе не действительны
    // bool isBreak;


    bool isUsed;

    int pt[2];
    int ptReal[2];
    int ptPrev[2];
    int ptPrevReal[2];
    int width;
    int height;
    int widthReal;
    int heightReal;

    double length;
    double angle;
};

typedef vector<Area>    Areas;
typedef vector<SeqArea> SeqAreas;
typedef deque<SeqAreas> SeqAreasBuffer;

#endif // PROCESSDATA_H

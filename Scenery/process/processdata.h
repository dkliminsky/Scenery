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

struct ContourPt {
    ContourPt(int x=0, int y=0) { this->x = x; this->y = y; }
    int x;
    int y;
};

typedef vector<Area>        Areas;
typedef vector<SeqArea>     SeqAreas;
typedef vector<ContourPt>   Contour;
typedef vector<Contour>     Contours;

struct ProcessData
{
public:
    int width;
    int height;

    Areas    areas;
    SeqAreas seqAreas;
    Contours contours;
};

typedef vector<ProcessData> ProcessDatas;

#endif // PROCESSDATA_H

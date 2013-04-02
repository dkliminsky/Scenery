#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
    Utils();

    int random(int high);
    bool chance(double probability);
    float distance(float x1, float y1, float x2, float y2);
    double distance(double x1, double y1, double x2, double y2);
    float angle(float x1, float y1, float x2, float y2);
};

#endif // UTILS_H

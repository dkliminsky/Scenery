#ifndef TOOLS_H
#define TOOLS_H

class Tools
{
public:
    static int random(int high);
    static bool chance(double probability);
    static float distance(float x1, float y1, float x2, float y2);
    static double distance(double x1, double y1, double x2, double y2);
    static float angle(float x1, float y1, float x2, float y2);
    static float pi();
};

#endif // TOOLS_H

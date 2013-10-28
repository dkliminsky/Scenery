#ifndef RECT_H
#define RECT_H

class Rect
{
public:
    Rect();
};

class RectF
{
public:
    RectF();
    RectF(float x1, float y1, float x2, float y2);
    RectF &operator=(const RectF &rectf);

    float x1;
    float y1;
    float x2;
    float y2;
};


#endif // RECT_H

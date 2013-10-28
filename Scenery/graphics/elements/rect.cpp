#include "rect.h"

Rect::Rect()
{
}


RectF::RectF()
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
}

RectF::RectF(float x1, float y1, float x2, float y2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

RectF &RectF::operator=(const RectF &rectf)
{
    this->x1 = rectf.x1;
    this->y1 = rectf.y1;
    this->x2 = rectf.x2;
    this->y2 = rectf.y2;
    return *this;
}

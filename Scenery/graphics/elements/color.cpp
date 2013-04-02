#include "color.h"
#include <math.h>

Color::Color(GLfloat r, GLfloat b, GLfloat g, GLfloat a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(const Color &color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}

Color &Color::operator=(const Color &color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
    return *this;
}

void Color::setRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Color::randomRGB()
{
    r = (GLfloat)rand()/RAND_MAX;
    g = (GLfloat)rand()/RAND_MAX;
    b = (GLfloat)rand()/RAND_MAX;
}

#ifndef VIEWEVENT_H
#define VIEWEVENT_H

class ViewEvent
{
public:
    ViewEvent(){}
    void virtual setup() = 0;
    void virtual paint() = 0;
    void virtual resize(int width, int height) = 0;
};

#endif // VIEWEVENT_H

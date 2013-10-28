#ifndef ISCENE_H
#define ISCENE_H

class IScene
{
public:
    IScene(){}
    ~IScene(){}

    void virtual setupEvent(void *){}
    void virtual paintEvent(){}
    void virtual resizeEvent(){}
};

#endif // ISCENE_H

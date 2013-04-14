#ifndef ISCENE_H
#define ISCENE_H

class IScene
{
public:
    IScene() {}
    void virtual setupEvent(void *view) = 0;
    void virtual paintEvent() = 0;
    void virtual resizeEvent(int width, int height) = 0;
    void virtual pushButton(int is) = 0;
};

#endif // ISCENE_H

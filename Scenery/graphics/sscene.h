#ifndef SSCENE_H
#define SSCENE_H

class SScene
{
public:
    SScene() {}
    virtual ~SScene(){}

    void virtual setupEvent(void *view) = 0;
    void virtual paintEvent() = 0;
    void virtual resizeEvent(int width, int height) = 0;
};

#endif // SSCENE_H

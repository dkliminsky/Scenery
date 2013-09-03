#ifndef SCENEPROCESS_H
#define SCENEPROCESS_H

#include "view.h"

class SceneProcess
{
public:
    SceneProcess();

    int width();
    int height();
    Areas &areas();
    SeqAreas &seqAreas();
    Contours &contours();
    Image *hit();
    Image *image();
    void command(QString name);

    void _setN(int n) { this->n = n; }
    void _setView(View *view) { this->view = view; }

private:
    View *view;
    int n;

    Areas _areas;
    SeqAreas _seqArea;
    Contours _contour;
    Image _hit;
    Image _image;
};

#endif // SCENEPROCESS_H

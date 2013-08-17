#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QDebug>
#include <math.h>
#include "sscene.h"
#include "view.h"

#include "actions/actionbutton.h"

#include "controls/controlbool.h"
#include "controls/controlint.h"
#include "controls/controldouble.h"
#include "controls/controlstring.h"
#include "controls/controlcolor.h"
#include "controls/controlimage.h"

class SceneProcess
{
public:
    SceneProcess(){}

    int width() {
        if (view->datas()->size() > n) return view->datas()->at(n)->getWidth();
        else return 0;
    }

    int height() {
        if (view->datas()->size() > n) return view->datas()->at(n)->getHeight();
        else return 0;
    }

    Areas &areas() {
        if (view->datas()->size() > n) return view->datas()->at(n)->getAreas();
        else return _areas;
    }

    SeqAreas &seqAreas() {
        if (view->datas()->size() > n) return view->datas()->at(n)->getSeqAreas();
        else return _seqArea;
    }

    Contours &contours() {
        if (view->datas()->size() > n) return view->datas()->at(n)->getContours();
        else return _contour;
    }

    Image *image() {
        if (view->datas()->size() > n) {
            _image.set(view->datas()->at(n)->getImage()->imageData,
                       view->datas()->at(n)->getImage()->width,
                       view->datas()->at(n)->getImage()->height,
                       view->datas()->at(n)->getImage()->nChannels);
        }
        return &_image;
    }

   void _setN(int n) { this->n = n; }
   void _setView(View *view) { this->view = view; }

private:
    View *view;
    int n;

    Areas _areas;
    SeqAreas _seqArea;
    Contours _contour;
    Image _image;
};

typedef QVector<Image *> Images;
typedef QVector<IControl *> Controls;
typedef QVector<ActionButton *> Actions;

class Scene: public SScene
{
public:
    Scene();
    ~Scene();

    // Scene APIs

    // Virtual functions
    virtual QString name() { return "Noname"; }
    virtual void setup(){}
    virtual void resize(){}
    virtual void paint(){}
    virtual void action(int){}

    // Graphics functions
    void size(int width, int height);
    int width();
    int height();

    void background(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
    void background(const Color &color);

    void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
    void color(const Color &color);

    void lineWidth(GLfloat width);
    void lineParts(int parts);
    void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    void line(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

    void bezier(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
                GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
    void bezier(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
                            GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);

    Image *loadImage(const QString &fileName);
    Image *createImage(int width, int height, int channels);
    Image *copyImage(Image *img);
    void image(Image *img, GLfloat x, GLfloat y,
                           GLfloat width, GLfloat height, GLfloat angle=0);
    void text(GLint x, GLint y, const QString & str,
                                const QFont & fnt = QFont());
    void flush();

    // Time function
    int time();
    int dtime();
    int fps();

    // Math function
    int random(int high);
    bool chance(double probability);
    float distance(float x1, float y1, float x2, float y2);
    double distance(double x1, double y1, double x2, double y2);
    float angle(float x1, float y1, float x2, float y2);

    // Control function
    void signal(int id);
    void button(int id, QString description);
    void control(int &x, QString description, int min=0, int max=999, int step=1);
    void control(double &x, QString description, double min=0, double max=100, int precision=1);
    void control(bool &x, QString description);
    void control(QString &string, QString description, QStringList list);
    void control(Color &color, QString description);
    void control(Image **image, QString description, QString path, QString file="");

    // Process function
    SceneProcess *process(int n);

    // Other
    Controls &controls() { return _controls; }
    Actions &actions() { return _actions; }

protected:
    void virtual setupEvent(void *view);
    void virtual paintEvent();
    void virtual resizeEvent();

private:
    View *view;
    SceneProcess _process;

    Images _images;
    Controls _controls;
    Actions _actions;

    Images imagesBuffer;
};

#endif // SCENE_H

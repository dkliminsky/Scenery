#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QStack>
#include <QQueue>
#include <QDebug>
#include <math.h>
#include "sscene.h"
#include "view.h"
#include "sceneprocess.h"

#include "controls/controlbool.h"
#include "controls/controlint.h"
#include "controls/controldouble.h"
#include "controls/controlstring.h"
#include "controls/controlcolor.h"
#include "controls/controlimage.h"
#include "controls/controlbutton.h"

typedef QVector<Image *> Images;
typedef QVector<IControl *> Controls;

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
    float pi();

    // Control function
    void signal(int id);
    void button(QString description, int id, QString name);
    void button(QString description, int id1, QString name1,
                                     int id2, QString name2);
    void button(QString description, int id1, QString name1,
                                     int id2, QString name2,
                                     int id3, QString name3);
    void button(QString description, int id1, QString name1,
                                     int id2, QString name2,
                                     int id3, QString name3,
                                     int id4, QString name4);
    void control(int &x, QString description, int min=0, int max=999, int step=1);
    void control(double &x, QString description, double min=0, double max=100, int precision=1);
    void control(bool &x, QString description);
    void control(QString &string, QString description, QStringList list);
    void control(Color &color, QString description);
    void control(Image **image, QString description, QString path, QString file="");

    // Process function
    SceneProcess *process(int n);

    // Controls
    Controls &controls() { return _controls; }

protected:
    void virtual setupEvent(void *view);
    void virtual paintEvent();
    void virtual resizeEvent();

private:
    View *view;
    SceneProcess _process;

    Images _images;
    Controls _controls;

    Images imagesBuffer;
};

#endif // SCENE_H

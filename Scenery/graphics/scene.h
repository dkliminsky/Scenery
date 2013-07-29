#ifndef SCENE_H
#define SCENE_H

#include "QString"
#include "sscene.h"
#include "view.h"

typedef QVector<Image *> Images;

class Scene: public SScene
{
public:
    Scene();

    // Virtual functions
    virtual QString name() { return "Noname"; }
    virtual void setup(){}
    virtual void paint(){}
    virtual void resize(int, int){}

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

    // Scene API: Control
    //void button(int id, QString description);
    //void control(int &x, QString description, int min=0, int max=100);
    //void control(double &x, QString description, double min=0, double max=100, int precision=1);
    //void control(bool &x, QString description);
    //void control(QString &string, QString description, QStringList list);
    //void control(Color &color, QString description);
    //void control(Image **image, QString description, QString path, QString file="");

    // Controls
    //QVector<IControl *> &getControls() { return controls; }

protected:
    void virtual setupEvent(void *view);
    void virtual paintEvent();
    void virtual resizeEvent(int width, int height);

private:
    View *view;
    Images imagesBuffer;
};

#endif // SCENE_H

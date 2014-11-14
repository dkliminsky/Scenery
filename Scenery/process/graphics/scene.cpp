#include "scene.h"

#include "tools.h"
#include "controls/controlbool.h"
#include "controls/controlint.h"
#include "controls/controldouble.h"
#include "controls/controlstring.h"
#include "controls/controlcolor.h"
#include "controls/controlimage.h"
#include "controls/controlbutton.h"


Scene::Scene()
{
    view = 0;
}

Scene::~Scene()
{
    for (int i=0; i<_images.size(); i++)
        delete _images[i];

    for (int i=0; i<_controls.size(); i++)
        delete _controls[i];
}

void Scene::size(int width, int height)
{
    view->graphic()->size(width, height);
}

int Scene::width()
{
    return view->graphic()->width();
}

int Scene::height()
{
    return view->graphic()->height();
}

void Scene::background(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    view->graphic()->background(r, g, b, a);
}

void Scene::background(const Color &color)
{
    view->graphic()->background(color);
}

void Scene::color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    view->graphic()->color(r, g, b, a);
}

void Scene::color(const Color &color)
{
    view->graphic()->color(color);
}

void Scene::lineWidth(GLfloat width)
{
    view->graphic()->lineWidth(width);
}

void Scene::lineParts(int parts)
{
    view->graphic()->lineParts(parts);
}

void Scene::line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    view->graphic()->line(x1, y1, x2, y2);
}

void Scene::line(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    view->graphic()->line(img, x1, y1, x2, y2);
}

void Scene::bezier(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    view->graphic()->bezier(x1, y1, x2, y2, x3, y3, x4, y4);
}

void Scene::bezier(Image *img, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    view->graphic()->bezier(img, x1, y1, x2, y2, x3, y3, x4, y4);
}

Image *Scene::loadImage(const QString &fileName)
{
    Image *image = new Image(fileName);
    _images += image;
    if (view) {
        image->bind();
    }
    else {
        // Если экземпляр view еще не доступен,
        // добавим изображения в буфер и вызовем
        // для них bind позднее, когда придет
        // сигнал setupEvent
        imagesBuffer += image;
    }
    return image;
}

Image *Scene::createImage(int width, int height, int channels)
{
    Image *image = new Image(width, height, channels);
    _images += image;
    return image;
}

Image *Scene::copyImage(Image *img)
{

}

void Scene::image(Image *img, GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat angle)
{
    view->graphic()->image(img, x, y, width, height, angle);
}

void Scene::text(GLint x, GLint y, const QString & str, const QFont & fnt)
{
    view->renderText(x, y, str, fnt);
}

void Scene::flush()
{
    view->graphic()->flush();
}

int Scene::time()
{
    return view->timing();
}

int Scene::dtime()
{
    return 0;
    //return view->dtime();
}

int Scene::fps()
{
    return 0;
    //return view->fps();
}

int Scene::random(int high)
{
    return Tools::random(high);
}

bool Scene::chance(double probability)
{
    return Tools::chance(probability);
}

float Scene::distance(float x1, float y1, float x2, float y2)
{
    return Tools::distance(x1, y1, x2, y2);
}

double Scene::distance(double x1, double y1, double x2, double y2)
{
    return Tools::distance(x1, y1, x2, y2);
}

float Scene::angle(float x1, float y1, float x2, float y2)
{
    return Tools::angle(x1, y1, x2, y2);
}

float Scene::pi()
{
    return Tools::pi();
}

void Scene::button(QString description, int id, QString name)
{
    QVector<ControlButton::Button> buttons;
    ControlButton::Button button;
    button.id = id;
    button.name = name;
    buttons += button;
    _controls += new ControlButton(description, buttons);
}

void Scene::button(QString description, int id1, QString name1,
                                        int id2, QString name2)
{
    QVector<ControlButton::Button> buttons;
    ControlButton::Button button;
    button.id = id1;
    button.name = name1;
    buttons += button;
    button.id = id2;
    button.name = name2;
    buttons += button;
    _controls += new ControlButton(description, buttons);
}

void Scene::button(QString description, int id1, QString name1,
                                        int id2, QString name2,
                                        int id3, QString name3)
{
    QVector<ControlButton::Button> buttons;
    ControlButton::Button button;
    button.id = id1;
    button.name = name1;
    buttons += button;
    button.id = id2;
    button.name = name2;
    buttons += button;
    button.id = id3;
    button.name = name3;
    buttons += button;
    _controls += new ControlButton(description, buttons);
}

void Scene::button(QString description, int id1, QString name1,
                                        int id2, QString name2,
                                        int id3, QString name3,
                                        int id4, QString name4)
{
    QVector<ControlButton::Button> buttons;
    ControlButton::Button button;
    button.id = id1;
    button.name = name1;
    buttons += button;
    button.id = id2;
    button.name = name2;
    buttons += button;
    button.id = id3;
    button.name = name3;
    buttons += button;
    button.id = id4;
    button.name = name4;
    buttons += button;
    _controls += new ControlButton(description, buttons);
}

void Scene::button(QString description, int id1, QString name1,
                                        int id2, QString name2,
                                        int id3, QString name3,
                                        int id4, QString name4,
                                        int id5, QString name5)
{
    QVector<ControlButton::Button> buttons;
    ControlButton::Button button;
    button.id = id1;
    button.name = name1;
    buttons += button;
    button.id = id2;
    button.name = name2;
    buttons += button;
    button.id = id3;
    button.name = name3;
    buttons += button;
    button.id = id4;
    button.name = name4;
    buttons += button;
    button.id = id5;
    button.name = name5;
    buttons += button;
    _controls += new ControlButton(description, buttons);
}

void Scene::button(QString description, int id1, QString name1,
                                        int id2, QString name2,
                                        int id3, QString name3,
                                        int id4, QString name4,
                                        int id5, QString name5,
                                        int id6, QString name6)
{
    QVector<ControlButton::Button> buttons;
    ControlButton::Button button;
    button.id = id1;
    button.name = name1;
    buttons += button;
    button.id = id2;
    button.name = name2;
    buttons += button;
    button.id = id3;
    button.name = name3;
    buttons += button;
    button.id = id4;
    button.name = name4;
    buttons += button;
    button.id = id5;
    button.name = name5;
    buttons += button;
    button.id = id6;
    button.name = name6;
    buttons += button;
    _controls += new ControlButton(description, buttons);
}

void Scene::control(int &x, QString description, int min, int max, int step)
{
    _controls += new ControlInt(x, description, min, max, step);
}

void Scene::control(double &x, QString description, double min, double max, int precision)
{
    _controls += new ControlDouble(x, description, min, max, precision);
}

void Scene::control(bool &x, QString description)
{
    _controls += new ControlBool(x, description);
}

void Scene::control(QString &string, QString description, QStringList list)
{
    _controls += new ControlString(string, description, list);
}

void Scene::control(Color &color, QString description)
{
    _controls += new ControlColor(color, description);
}

void Scene::control(Image **image, QString description, QString path, QString file)
{
    *image = loadImage(path + file);
}

void Scene::signal(int id)
{
    action(id);
}

Port *Scene::process(int n)
{
    Q_ASSERT(view->in.count() > n);
    return view->in[n];
}

void Scene::setupEvent(void *view)
{
    this->view = static_cast<ViewNode *>(view);
    for(int i=0; i<imagesBuffer.size(); i++) {
        imagesBuffer.at(i)->bind();
    }
    imagesBuffer.clear();
    setup();
}

void Scene::paintEvent()
{
    paint();
}

void Scene::resizeEvent()
{
    resize();
}

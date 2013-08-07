#include "scene.h"

Scene::Scene()
{
    view = 0;
}

Scene::~Scene()
{
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
    if (view) {
        view->bindImage(image);
    }
    else {
        // Если экземпляр view еще не доступен,
        // добавим изображения в буфер и вызовем
        // для них bindImage позднее, когда придет
        // экземпляр view
        imagesBuffer.append(image);
    }
    return image;
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
    return view->time();
}

int Scene::dtime()
{
    return view->dtime();
}

int Scene::fps()
{
    return view->fps();
}

int Scene::random(int high)
{
    return view->utils()->random(high);
}

bool Scene::chance(double probability)
{
    return view->utils()->chance(probability);
}

float Scene::distance(float x1, float y1, float x2, float y2)
{
    return view->utils()->distance(x1, y1, x2, y2);
}

double Scene::distance(double x1, double y1, double x2, double y2)
{
    return view->utils()->distance(x1, y1, x2, y2);
}

float Scene::angle(float x1, float y1, float x2, float y2)
{
    return view->utils()->angle(x1, y1, x2, y2);
}

void Scene::signal(int id, QString description)
{

}

void Scene::control(int &x, QString description, int min, int max)
{

}

void Scene::control(double &x, QString description, double min, double max, int precision)
{

}

void Scene::control(bool &x, QString description)
{
    _controls += new ControlBool(x, description);
}

void Scene::control(QString &string, QString description, QStringList list)
{

}

void Scene::control(Color &color, QString description)
{

}

void Scene::control(Image **image, QString description, QString path, QString file)
{
    *image = loadImage(path + file);
}

SceneProcess *Scene::process(int n)
{
    _process._setView(view);
    _process._setN(n);
    return &_process;
}

void Scene::setupEvent(void *view)
{
    this->view = static_cast<View *>(view);
    for(int i=0; i<imagesBuffer.size(); i++) {
        this->view->bindImage(imagesBuffer.at(i));
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

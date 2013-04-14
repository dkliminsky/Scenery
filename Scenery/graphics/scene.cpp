#include "scene.h"
#include <QtGlobal>
#include <QLayout>
#include <QLabel>
#include <QSlider>
#include <QDir>
#include <QDebug>

Scene::Scene()
{
    qDebug() << "Constructor Begin: Scene";

    setProcessCount(1);
    firstPaint = true;

    // Controls
    widget = new QWidget();
    layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    //layout->setSpacing(3);
    widget->setLayout(layout);

    qDebug() << "Constructor End: Scene";
}

void Scene::setProcessCount(int n)
{
    seqAreasVector.resize(n);
    areasVector.resize(n);
    widthVector.resize(n);
    heightVector.resize(n);
    contoursVector.resize(n);
}

void Scene::setupEvent(void *view)
{
    qDebug() << "Scene changed!";
    this->view = static_cast<View *>(view);
    sceneChanged();
    firstPaint = true;
}

void Scene::paintEvent()
{
    if (firstPaint) {
        firstPaint = false;
        setup();
    }

    updateSize();
    paint();
    flush();
    updateControlData();
}

void Scene::resizeEvent(int width, int height)
{
    widthView = width;
    heightView = height;
}

void Scene::pushButton(int id)
{
    push(id);
}

void Scene::updateControlData()
{
    for (int i = 0; i < controls.count(); ++i) {
        controls.at(i)->updateData();
    }
}

int &Scene::getWidth(int n)
{
    Q_ASSERT(n < widthVector.size());
    return widthVector[n];
}

int &Scene::getHeight(int n)
{
    Q_ASSERT(n < heightVector.size());
    return heightVector[n];
}

Areas &Scene::getAreas(int n)
{
    Q_ASSERT(n < areasVector.size());
    return areasVector[n];
}

SeqAreas &Scene::getSeqAreas(int n)
{
    Q_ASSERT(n < seqAreasVector.size());
    return seqAreasVector[n];
}

Contours &Scene::getContours(int n)
{
    Q_ASSERT(n < contoursVector.size());
    return contoursVector[n];
}

int Scene::time()
{
    Q_ASSERT(view);
    return view->getTimeScene();
}

int Scene::dtime()
{
    Q_ASSERT(view);
    return view->getPaintTimeScene();
}


void Scene::button(int &x, QString description, int min, int max)
{
    ControlInt *data = new ControlInt(x, min, max);
    addWidgetValue(data, description);
    controls.append(data);
}

void Scene::button(double &x, QString description, double min, double max, int precision)
{
    ControlDouble *data = new ControlDouble(x, min, max, precision);
    addWidgetValue(data, description);
    controls.append(data);
}

void Scene::button(bool &x, QString description)
{
    ControlBool *data = new ControlBool(x);
    addWidgetValue(data, description);
    controls.append(data);
}

void Scene::button(QString &string, QString description, QStringList list)
{
    ControlString *data = new ControlString(string, list);
    addWidgetValue(data, description);
    controls.append(data);
}

void Scene::button(Color &color, QString description)
{
    ControlColor *data = new ControlColor(color);
    addWidgetValue(data, description);
    controls.append(data);
}

void Scene::button(Image **image, QString description, QString path, QString file)
{
    QDir dir(path);
    Q_ASSERT(dir.exists());
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    QStringList list = dir.entryList(filters);

    if (list.size() == 0) {
        *image = loadImage();
        return;
    }

    QVector<Image *> images;
    int index = 0;
    for (int i = 0; i < list.size(); i++) {
        QString name = list.at(i);
        Image *imageDir = new Image(path + name);
        images.append(imageDir);
        addImage(imageDir);

        if (name == file) {
            index = i;
        }
    }

    *image = images.at(index);

    ControlImage *data = new ControlImage(image, images, index);
    addWidgetValue(data, description);
    controls.append(data);
}

void Scene::button(int id, QString description)
{
    ControlButton *data = new ControlButton(this, id, description);
    addWidgetValue(data, "Button");
}

void Scene::addWidgetValue(QWidget *widget, QString description)
{
    int row = layout->rowCount();
    layout->addWidget(new QLabel(description), row, 1);
    layout->addWidget(widget, row, 2);
}


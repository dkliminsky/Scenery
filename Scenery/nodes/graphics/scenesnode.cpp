#include "scenesnode.h"

ScenesNode::ScenesNode() :
    _scene(nullptr)
{
    startTimer(17);
}

ScenesNode::~ScenesNode()
{

}

void ScenesNode::setScene(Scene *scene)
{
    _scene = scene;
    _scene->_inputs = &inputs;
    _view.setScene(scene);
}

void ScenesNode::timerEvent(QTimerEvent *)
{
    _view.update();
}


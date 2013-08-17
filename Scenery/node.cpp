#include "node.h"

Node::Node(QString name)
{
    this->name = name;

    width = 0;
    height = 0;

    imageResult = 0;
    hitResult = 0;
}

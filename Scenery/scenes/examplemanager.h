#ifndef EXAMPLEMANAGER_H
#define EXAMPLEMANAGER_H

#include "nodes/manager.h"
#include "nodes/nodes.h"

#include "scenes/defaultscene.h"
#include "scenes/shadowscene.h"


class ExampleManager : public Manager
{
public:
    void initScene();

private:
    //ViewNode *viewNode;

};

#endif // EXAMPLEMANAGER_H

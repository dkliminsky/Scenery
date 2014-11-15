#include "scenes\examplekinectmanager.h"


void ExampleKinectManager::initScene()
{
	Node *kinectNode = new KinectNode();
	kinectNode->setPos(0, 0);
	sources.append(kinectNode);
	nodes.append(kinectNode);

	Node *debugNode1 = new DebugNode();
	debugNode1->setPos(200, 0);
	nodes.append(debugNode1);

	kinectNode->out.at(0)->links.append(new Link(debugNode1, 0));

}
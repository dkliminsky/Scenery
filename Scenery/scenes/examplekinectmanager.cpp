#include "scenes\examplekinectmanager.h"


void ExampleKinectManager::initScene()
{
	Node *kinectNode = new KinectNode();
	kinectNode->setPos(0, 0);
	sources.append(kinectNode);
	nodes.append(kinectNode);

	Node *debugColorNode = new DebugNode();
	debugColorNode->setPos(200, 0);
	nodes.append(debugColorNode);

	Node *debugDepthNode = new DebugNode();
	debugDepthNode->setPos(200, 50);
	nodes.append(debugDepthNode);

	kinectNode->out.at(0)->links.append(new Link(debugColorNode, 0));
	kinectNode->out.at(1)->links.append(new Link(debugDepthNode, 0));
}
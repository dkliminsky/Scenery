#include "gesturenode.h"

GestureNode::GestureNode()
{
    METHOD_BEGIN

    inputs.append(new Port(PortType::Human));
    outputs.append(new Port(PortType::Booleans));

    METHOD_END
}

void GestureNode::run()
{
    Human &human = inputs.at(0)->human;
    vector<bool> &booleans = outputs.at(0)->booleans;

    booleans.resize(2);
    if (human.isTracking) {
        float a = angle(human.spine.x, human.spine.y,
                        human.shoulderCenter.x, human.shoulderCenter.y);
        float a_min = pi()/2/3;

       // qDebug() << a << a_min;

        booleans[0] = false;
        if (a < pi()/2 - a_min) {
            booleans[0] = true;
        }

        booleans[1] = false;
        if (a > pi()/2 + a_min) {
            booleans[1] = true;
        }

    }
}


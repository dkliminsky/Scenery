#include "gesturenode.h"

GestureNode::GestureNode()
{
    METHOD_BEGIN

    inputs.append(new Port(PortType::Human));
    outputs.append(new Port(PortType::Booleans));

    addControl(inclination_deg=45, "Inclination", 0, 90);
    addControl(time_interval=5000, "Time Interval", 0, 10000);

    time.start();

    gest_time = 0;
    gest_start = false;

    METHOD_END
}

void GestureNode::run()
{
    Human &human = inputs.at(0)->human;
    vector<bool> &booleans = outputs.at(0)->booleans;
    timer = time.elapsed();


    booleans.resize(2);
    booleans[0] = false;
    booleans[1] = false;

//    qDebug() << timer << gest_time << timer - gest_time;

    if (gest_start && timer - gest_time < time_interval) {
//        qDebug() << "!!";
        return;

    }

    gest_start = false;


    if (human.isTracking) {
        float a = angle(human.spine.x, human.spine.y,
                        human.shoulderCenter.x, human.shoulderCenter.y);
        float a_min = inclination_deg * pi() / 180;

       // qDebug() << a << a_min;


        if (a < pi()/2 - a_min) {
            booleans[0] = true;
            if ( !gest_start) {
                gest_start = true;
                gest_time = timer;
            }

        }

        if (a > pi()/2 + a_min) {
            booleans[1] = true;
            if ( !gest_start) {
                gest_start = true;
                gest_time = timer;
            }
        }

    }
}


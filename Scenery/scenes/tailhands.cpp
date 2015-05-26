#include <cmath>
#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;


class TailHandsScene : public Scene
{
public:
    QString name() { return "Tail Hands"; }

    Color backColor;
    Color tailColor;
    Image *tailImage;
    int tailSize;
    Image *blotImages[5];

    Color tailRandColor;
    bool isRandColor;
    int rand_color_time;


    int next_time;

    TailHandsScene()
    {
        addControl(backColor=Color(0, 0, 0, 0.2f), "Back color");
        addControl(tailColor=Color(1, 0, 0, 1), "Tail color");
        addControl(tailSize=20, "Tail Size", 0, 50);
        addControl(isRandColor=false, "Rand Color");
        addControl(rand_color_time=500, "Rand Color Time", 0, 5000);
        //addControl(&tailImage, "Tail hands", "images/forms/", "circle01.png");

        blotImages[0] = new Image("images/forms/blot01.png");
        blotImages[1] = new Image("images/forms/blot02.png");
        blotImages[2] = new Image("images/forms/blot03.png");
        blotImages[3] = new Image("images/forms/blot04.png");
        blotImages[4] = new Image("images/forms/blot05.png");
        next_time = 0;
    }

    virtual void paint()
    {
        Rect pos = input("rect")->rect;
        Human &human = input("human1")->human;
        human.translate(pos);

        size(320, 240);
        background(backColor);

        if (isRandColor) {
            if (next_time < time()) {
                next_time = time() + rand_color_time;
                tailRandColor = Color((random(255))/255.0f,
                                      (random(255))/255.0f,
                                      (random(255))/255.0f);
            }
            color(tailRandColor);
        }
        else {
            color(tailColor);
        }

        if (human.isTracking) {
            draw(blotImages[random(5)], human.wristRight.x, human.wristRight.y, tailSize, tailSize);
            draw(blotImages[random(5)], human.wristLeft.x, human.wristLeft.y, tailSize, tailSize);
        }
    }
};

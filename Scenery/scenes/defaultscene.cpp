#include "defaultscene.h"

DefaultScene::DefaultScene()
{
}

void DefaultScene::setup()
{
    imageShip = new Image("resources/images/ship.png");
    imageShip->bind();

    imageStream = new Image();
}

void DefaultScene::resize()
{
    background(1, 1, 1, 1);
}

void DefaultScene::paint()
{
    size(200, 200);
    background(1, 1, 1, 1);

    color(1, 1, 1, 1);
    image(imageShip, 50, 50, 90, 90);

    imageStream->set(process(0)->mat);
    imageStream->bind();

    image(imageStream, 150, 150, 90, 90);


}

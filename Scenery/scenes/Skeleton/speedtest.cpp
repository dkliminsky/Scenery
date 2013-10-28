#include "speedtest.h"

SpeedTest::SpeedTest()
{
    control(&imageSprite, "Sprite", "images/test/", "sprite.png");
    control(&images[0], "Image1", "images/test/", "image1.png");
    control(&images[1], "Image2", "images/test/", "image2.png");
    control(&images[2], "Image3", "images/test/", "image3.png");
    control(&images[3], "Image4", "images/test/", "image4.png");

    control(sizeImage=30, "Size");
    control(count=1000, "Count", 0, 100000, 1000);
}

void SpeedTest::paint()
{
    size(width(), height());

    for (int i=0; i<count; i++) {
        Color c;
        c.randomRGB();
        color(c);
        float x = random(width());
        float y = random(height());

//        int n = random(4);
//        if (n == 0) {
//            imageSprite->setTexCoords(0, 0, 0.5, 0.5);
//        }
//        else if (n == 1) {
//            imageSprite->setTexCoords(0.5, 0, 1.0, 0.5);
//        }
//        else if (n == 2) {
//            imageSprite->setTexCoords(0.0, 0.5, 0.5, 1.0);
//        }
//        else if (n == 3) {
//            imageSprite->setTexCoords(0.5, 0.5, 1.0, 1.0);
//        }
//        image(imageSprite, x, y, sizeImage, sizeImage);

        //int n = random(4);
        //image(images[n], x, y, sizeImage, sizeImage);

        float x2 = random(width());
        float y2 = random(height());
        line(x, y, x2, y2);

    }
}

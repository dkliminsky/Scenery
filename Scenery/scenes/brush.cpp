#include "brush.h"

Brush::Brush()
{
    control(isStroke=true, "Enable stroke");
    control(strokeColor=Color(1,1,1,1), "Stroke Color");
    control(strokeSize=50, "Stroke size", 0, 300);
    control(strokeLimit=3, "Stroke speed limit", 0, 100);

    control(isBlot=false, "Enable blot");
    control(blotColor=Color(1,1,1,1), "Blot Color");
    control(blotSize=100, "Blot size", 0, 300);
    control(blotLimit=50, "Blot Speed limit", 0, 100);

    strokeImages[0] = loadImage("images/brushes/stroke01.png");
    strokeImages[1] = loadImage("images/brushes/stroke02.png");
    strokeImages[2] = loadImage("images/brushes/stroke03.png");
    strokeImages[3] = loadImage("images/brushes/stroke04.png");

    blotImages[0] = loadImage("images/brushes/blot01.png");
    blotImages[1] = loadImage("images/brushes/blot02.png");
    blotImages[2] = loadImage("images/brushes/blot03.png");
    blotImages[3] = loadImage("images/brushes/blot04.png");
    blotImages[4] = loadImage("images/brushes/blot05.png");
}

void Brush::setup()
{
    size(getWidth(0), getHeight(0));
    background(0.0f, 0.0f, 0.0f, 1.0f);
}

void Brush::paint()
{
    color(strokeColor);
    SeqAreas &seqAreas = getSeqAreas(0);
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        if (seqArea.number > 1) {

            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
            GLfloat envColor1[4] = {strokeColor.r, strokeColor.g, strokeColor.b, 0};
            glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor1);

            if ( isStroke && seqArea.length > strokeLimit) {
                float x = seqArea.pt[0] - (seqArea.pt[0] - seqArea.ptPrev[0])/2.0;
                float y = seqArea.pt[1] - (seqArea.pt[1] - seqArea.ptPrev[1])/2.0;
                image(strokeImages[random(4)], x, y,
                      seqArea.length*1.1, strokeSize, seqArea.angle);
            }

            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
            GLfloat envColor2[4] = {blotColor.r, blotColor.g, blotColor.b, 0};
            glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor2);

            if ( isBlot && seqArea.length > blotLimit) {
                float x = seqArea.pt[0];
                float y = seqArea.pt[1];
                image(blotImages[random(5)], x, y,
                      blotSize, blotSize, random(360)/2.0*M_PI);
            }
        }
    }

    /*
    color(1,1,1,1);
    image(imgStroke, 25, 25, 70+10, 150, -M_PI/4.0);
    image(imgStroke, 75, 50, 50+10, 150, 0);
    image(imgStroke, 100, 75, 50+10, 150, -M_PI/2.0);
    image(imgStroke, 125, 75, 70+10, 150, M_PI/4.0);
    */
}

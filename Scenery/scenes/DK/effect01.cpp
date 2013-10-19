#include "effect01.h"

Effect01::Effect01()
{
    control(backColor=Color(0,0,0,1), "Background");
    control(treeColor=Color(1,0,0,1), "Tree color");
    control(treeWidth=3, "Tree width", 0, 10);
    control(treeTTL=30, "Tree ttl", 0, 500);
    control(treeTTLDisappear=20, "Tree ttl disappear", 0, 500);
    control(treeAlphaDisappear=0.05, "Tree alpha disappear", 0, 1, 2);
    control(treeWidhtDisappear=0.5, "Tree width disappear", 0, 1, 2);
    control(treeGrow=7, "Tree grow", 0, 100);
    control(treeGrowLenght=2, "Tree grow lenght", 0, 10);
    control(treeGrowDisappear=1, "Tree grow disappear", 0, 10);
    control(treeMaxLevel=3, "Tree max level", 0, 10);
    control(treeDeviation=30, "Tree deviation", 0, 100);

    control(treeProbNothing=0, "Tree prob nothing", 0, 10);
    control(treeProb0=0, "Tree prob 0", 0, 10);
    control(treeProb45=0, "Tree prob 45", 0, 10);
    control(treeProb90=10, "Tree prob 90", 0, 10);
    control(treeProbTree=0, "Tree prob tree", 0, 10);
}

void Effect01::setup()
{
    background(0, 0, 0);
}

void Effect01::paint()
{
    int w = process(0)->width();
    int h = process(0)->height();

    size(process(0)->width(), process(0)->height());
    background(backColor);

//    Image *frame = process(0)->image();
//    frame->bind();
//    color(1,1,1,1);
//    image(frame, w/2, h/2, w, h);
//    flush();

    SeqAreas &seqAreas = process(1)->seqAreas();
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        if (seqArea.number > 1 && seqArea.isUsed == false) {
            Tree tree;
            tree.x = seqArea.pt[0] + (random(treeDeviation) - treeDeviation/2);
            tree.y = seqArea.pt[1] + (random(treeDeviation) - treeDeviation/2);
            tree.angle = seqArea.angle;
            tree.lenght = 0;
            tree.level = 0;
            tree.grow = treeGrow;
            tree.ttl = treeTTL;
            tree.color = treeColor;
            tree.width = treeWidth;
            tree.isChildCreate = false;
            trees += tree;
        }
    }

    QList<Tree>::iterator ib = treesBuf.begin();
    while (ib != treesBuf.end()) {
        Tree &tree = *ib;
        trees += tree;
        ib = treesBuf.erase(ib);
    }

    QList<Tree>::iterator i = trees.begin();
    while (i != trees.end()) {
        Tree &tree = *i;
        if (tree.ttl > 0) {
            tree.ttl--;

            if (tree.ttl < treeTTLDisappear) {
                tree.color.a-=treeAlphaDisappear;
                if (tree.color.a < 0)
                    tree.color.a = 0;
            }

            if (tree.grow > 0) {
                tree.grow--;
                tree.lenght += treeGrowLenght;
            }
            else if (tree.level < treeMaxLevel && tree.isChildCreate == false) {
                tree.isChildCreate = true;

                int prob = treeProbNothing + treeProb0 + treeProb45 + treeProb90 + treeProbTree;
                int prob0 = treeProbNothing + treeProb0;
                int prob45 = treeProbNothing + treeProb0 + treeProb45;
                int prob90 = treeProbNothing + treeProb0 + treeProb45 + treeProb90;
                int probResult = random(prob) + 1;

                int sign = random(2);
                if (sign == 0) {
                    sign = 1;
                }
                else {
                    sign = -1;
                }

                if (probResult > treeProbNothing) {

                    Tree treeNew;
                    treeNew.x = tree.x + tree.lenght*cos(tree.angle);
                    treeNew.y = tree.y + tree.lenght*sin(tree.angle);

                    if (prob < prob0)
                        treeNew.angle = tree.angle;
                    else if (prob < prob45)
                        treeNew.angle = tree.angle + M_PI_4*sign;
                    else if (prob < prob90)
                        treeNew.angle = tree.angle + M_PI_2*sign;

                    treeNew.lenght = 0;
                    treeNew.level = tree.level + 1;
                    treeNew.grow = treeGrow - treeGrowDisappear * treeNew.level;
                    treeNew.ttl = treeTTL;
                    treeNew.color = treeColor;

                    treeNew.width = tree.width - treeWidhtDisappear;
                    if (treeNew.width < 0)
                        treeNew.width = 0;

                    treeNew.isChildCreate = false;
                    treesBuf += treeNew;

                }
            }

            i++;
        }
        else {
            i = trees.erase(i);
        }
    }

    QList<Tree>::iterator ic = trees.begin();
    while (ic != trees.end()) {
        Tree &tree = *ic;
        float x2 = tree.x + tree.lenght*cos(tree.angle);
        float y2 = tree.y + tree.lenght*sin(tree.angle);

        color(tree.color);
        lineWidth(tree.width);
        line(tree.x, tree.y, x2, y2);

        ic++;
    }
}

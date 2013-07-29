#ifndef PROCESS_H
#define PROCESS_H

#include "clustering.h"
#include "processdata.h"
#include "processfilters.h"

#include <QThread>
#include <QTime>

#include <opencv/cxcore.h>
#include <opencv/cvaux.h>

#include <string>
#include <list>
#include <vector>

using std::string;
using std::list;
using std::vector;


class Process : public ProcessFilters, public QThread, public Clustering
{
public:
    Process(int width, int height);
    ~Process();

    int getWidth() { return width; }
    int getHeight() { return height; }

    void step();


    // ====================================================================
    // Input
    // ====================================================================

    enum Mode {
        ProcessNone,
        ProcessColor,
        ProcessMotion,
        ProcessHaar,
        ProcessContour,
        ProcessHoughCircles
    };
    void setMode(Mode mode) { this->mode = mode; }
    Mode getMode() { return mode; }

    void setImage(IplImage *image);
    IplImage *getImage() { return image; }

    // ====================================================================
    // Output
    // ====================================================================

    // Возвращает одноканальную картинку с отмеченными
    // точками: 0 - не подходящий пиксель, 1 - подходящий
    IplImage *getHitImage() { return hitImage; }

    // Возвращает структуру с найдеными регионами
    Areas &getAreas() { return areas; }

    // Возвращает структуру с последовательностью регионов
    SeqAreas &getSeqAreas() { return *seqAreasResult; }

    //
    Contours &getContours() { return contours; }

    // ====================================================================
    // Color Parameters
    // ====================================================================

    enum ColorRangeMode {
        AllRange,
        HRange,
        HSminVminRange
    };

    struct ColorRangeParam {
        bool invert;            // Инвертировать значения

        unsigned char Hmin;    // Минимум цветового тона
        unsigned char Hmax;    // Максимум цветового тона

        unsigned char Smin;    // Минимум насыщенности
        unsigned char Smax;    // Максимум насыщенности

        unsigned char Vmin;    // Минимум яркости
        unsigned char Vmax;    // Максимум яркости
    };

    void setColorRangeMode(ColorRangeMode mode) { colorRangeMode = mode; }
    ColorRangeMode getColorRangeMode() { return colorRangeMode; }

    void setColorRangeParam(ColorRangeParam param) { colorRangeParam = param; }
    ColorRangeParam getColorRangeParam() { return colorRangeParam; }

    // ====================================================================
    // Motion Parameters
    // ====================================================================

    struct MotionParam {
        int sensitivity;
    };

    void setMotionParam(MotionParam param) { motionParam = param; }

    // ====================================================================
    // Haar Parameters
    // ====================================================================

    struct HaarParam {
        double scaleFactor;
        int minSizeX;
        int minSizeY;
        int maxSizeX;
        int maxSizeY;
    };

    void setHaarFile(string file);
    void setHaarParam(HaarParam param);

    // ====================================================================
    // Contour Parameters
    // ====================================================================

    struct ContourParam {
        int threshold1; // Границы поиска
        int threshold2;
    };

    void setContourParam(ContourParam param);

    // ====================================================================
    // HoughCircles Parameters
    // ====================================================================

    struct HoughCirclesParam {
        double inverseRatio;
        int minDistance;
        int param1;
        int param2;
        int minRadius;
        int maxRadius;
    };

    void setHoughCircleParam(HoughCirclesParam param) { houghCirclesParam = param; }

    // ====================================================================
    // Sequences Parameters
    // ====================================================================
    struct SeqAreaParam {
        int count;
        double lenghtLimit;
    };

    struct FilterSeqAreaParam {
        unsigned int buffSize;
    };

    void setSeqAreaParam(SeqAreaParam param);
    void setFilterSeqAreaParam(FilterSeqAreaParam param);

    // ====================================================================
    // Transform2D Parameters
    // ====================================================================

    struct Transform2DParam {
        double mx;
        double my;
        double sx;
        double sy;
        double theta;
        double h;
        double g;

        double deepHx;
        double deepHy;
        double deepHs;
    };

    void setTransform2DParam(Transform2DParam param) { trans2D = param; }
    void transform2D(int px, int py, int &qx, int &qy);
    void transform2DContrary(int px, int py, int &qx, int &qy);

protected:
    void run();

    // ====================================================================
    // Вспомогательные функции
    // ====================================================================

    // Установить все параметры по умолчанию
    void setDefaultParam();

    // Поиск последовательностей регионов
    void findSeqAreas(Areas &areas, SeqAreas &seqAreas);

    // Фильтр последовательностей регионов
    void filterSeqAreas(SeqAreas &seqAreas, SeqAreasBuffer &seqAreasBuffer);

private:
    int width;   // Ширина и высота изображений,
    int height;  // которые будут обрабатываться

    int timeMean;
    int timeNum;

    // ====================================================================
    // Input
    // ====================================================================

    Mode mode;
    IplImage *image;

    // ====================================================================
    // Общие свойства
    // ====================================================================

    Areas areas;
    SeqAreas seqAreas;
    SeqAreas *seqAreasResult;
    SeqAreasBuffer seqAreasBuffer;

    IplImage *hitImage;    // Одноканальное изображение с найденными пикселями

    IplImage *grayImage;
    IplImage *prevImage;

    // ====================================================================
    // Color
    // ====================================================================

    ColorRangeMode colorRangeMode;
    ColorRangeParam colorRangeParam;

    // Находит на изображении регионы с нужным цветовым диапазоном,
    void findColor();

    // ====================================================================
    // Motion
    // ====================================================================

    MotionParam motionParam;
    void findMotion();

    // ====================================================================
    // Haar
    // ====================================================================

    HaarParam haarParam;
    CvHaarClassifierCascade *haarCascade;
    CvMemStorage* haarStorage;

    void findHaar();

    // ====================================================================
    // Contour
    // ====================================================================
    Contours contours;

    ContourParam contourParam;

    CvMemStorage* contourStorage;
    CvMemStorage* hullsStorage;

    CvSeq* contoursSeq;
    CvSeq* hullsSeq;

    void findContours();
    //CvSeq *getContours() { return contoursSeq; }

    void findHulls();
    //CvSeq *getHulls() { return hullsSeq; }

    // ====================================================================
    // HoughCircles
    // ====================================================================

    HoughCirclesParam houghCirclesParam;

    CvMemStorage* houghCirclesStorage;

    void findHoughCircles();

    // ====================================================================
    // Sequences
    // ====================================================================
    SeqAreaParam seqAreaParam;
    FilterSeqAreaParam filterSeqAreaParam;

    // ====================================================================
    // Transform Parameters
    // ====================================================================

    Transform2DParam trans2D;
    void transform2DArea(Area &area);
    void transform2DAreas(Areas &areas);

};

#endif // PROCESS_H

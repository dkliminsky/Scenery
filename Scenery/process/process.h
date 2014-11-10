#ifndef PROCESS_H
#define PROCESS_H

#include "graphics/nodetemp.h"
#include "clustering.h"
#include "processdata.h"
#include "processfilters.h"
#include "processtools.h"

#include <QThread>
#include <QTime>

#include "opencv2/core/core_c.h"
#include "opencv2/video/background_segm.hpp"
#include <opencv/cvaux.h>

#include <string>
#include <list>
#include <vector>

using std::string;
using std::list;
using std::vector;
using std::deque;

typedef deque<SeqAreas> SeqAreasBuffer;


class Process : public NodeTemp, public ProcessTools, public QThread, public Clustering
{
public:
    Process(QString getName, int width, int height);
    ~Process();

    void step();
    void copyData();

    void setDebug(bool isDebug) { this->isDebug = isDebug; }
    bool getDebug() { return isDebug; }

    int getTime() { return timeResult; }

    void setCommand(QString name);

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
    // Subtraction Parameters
    // ====================================================================

    struct SubtractionImageParam {
        int history;
        float varThreshold;
        bool bShadowDetection;

        int nmixtures;
        double backgroundRatio;
        double noiseSigma;
    };

    void setSubtractionImageParam(SubtractionImageParam param) { subtractionImageParam = param; }
    void subtractionImageStart() { subtractionImageData.commandStart = true; }
    void subtractionImageStop() { subtractionImageData.commandStop = true; }

    void subtractionHitAdd(int n=1) { subtractionHitData.commandAddSeveral += n; }
    void subtractionHitClear() { subtractionHitData.commandClear = true; }

    IplImage *getHitSubtraction() { return hitSubImage; }
    IplImage *getBack() { return backImage; }

    // ====================================================================
    // Filters Parameters
    // ====================================================================

    struct FilterHitParam {
        int erodeIteration;
        int dilateIteration;
    };

    void setFilterHitParam(FilterHitParam param) { filterHitParam = param; }

    // ====================================================================
    // Areas & Sequences Parameters
    // ====================================================================
    struct FilterAreaParam {
        bool isFilterOutframe;
    };

    struct SeqAreaParam {
        int count;
        double lenghtLimit;
    };

    struct FilterSeqAreaParam {
        unsigned int buffSize;
    };

    void setSeqAreaParam(SeqAreaParam param);
    void setFilterAreaParam(FilterAreaParam param);
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

    // Фильтр регионов
    void filterAreas(Areas &areas);

    // Фильтр последовательностей регионов
    void filterSeqAreas(SeqAreas &seqAreas, SeqAreasBuffer &seqAreasBuffer);

private:
    bool isDebug;

    int timeMean;
    int timeNum;
    int timeResult;

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
    SeqAreas *seqAreasLast;
    SeqAreasBuffer seqAreasBuffer;

    IplImage *hitImage;    // Одноканальное изображение с найденными пикселями
    IplImage *hitSubImage; // Вычитание найденных пикселей

    IplImage *grayImage;
    IplImage *prevImage;

    IplImage *backImage;
    IplImage *foreImage;

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

    void processContoursHit();
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
    // Subtraction Parameters
    // ====================================================================

    struct SubtractionHitImage {
        bool commandStart;
        bool commandStop;
        bool commandChangeParam;
    } subtractionImageData;

    struct SubtractionHitData {
        bool isSubtraction;
        int commandAddSeveral;
        bool commandClear;
    } subtractionHitData;

    //cv::BackgroundSubtractor *backSubtractor;
    cv::BackgroundSubtractorMOG2 *backSubtractor;
    SubtractionImageParam subtractionImageParam;

    void processSubtractionImage();
    void processSubtractionHit();

    // ====================================================================
    // Filters Parameters
    // ====================================================================

    FilterHitParam filterHitParam;
    void processFiltersHit();

    // ====================================================================
    // Areas & Sequences
    // ====================================================================

    SeqAreaParam seqAreaParam;
    FilterAreaParam filterAreaParam;
    FilterSeqAreaParam filterSeqAreaParam;

    // ====================================================================
    // Transform Parameters
    // ====================================================================

    Transform2DParam trans2D;
    void transform2DAreas(Areas &areas);
    void transform2DArea(Area &area);

    void transform2DContours(Contours &contours);
    void transform2DContour(Contour &contour);

    // ====================================================================
    // Commands
    // ====================================================================

    struct Command {
        QString name;
    };
    vector<Command> commands;
    void realizeCommands();

};

#endif // PROCESS_H

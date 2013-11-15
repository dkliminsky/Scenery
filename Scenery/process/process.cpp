#include "process.h"

#include <QDebug>
#include <typeinfo>

Process::Process(QString name, int width, int height) :
    Node(name)
{
    qDebug() << "Constructor Begin: Process";

    Q_ASSERT(width > 0 && height > 0);

    this->width  = width;
    this->height = height;

    isDebug = false;

    timeMean = 0;
    timeNum = 0;
    timeResult = 0;

    imageResult = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 3 );
    hitResult = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );

    // Common
    image = 0;
    grayImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );
    prevImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 3 );

    backImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 3 );
    foreImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 3 );

    hitImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );
    hitSubImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );

    // Color & Motion

    // Haar
    haarCascade = 0;
    haarStorage = cvCreateMemStorage(0);

    // Contour
    contourStorage = cvCreateMemStorage(0);
    approxStorage = cvCreateMemStorage(0);
    hullsStorage = 0;

    // HoughCircles
    houghCirclesStorage = cvCreateMemStorage(0);

    // Subtraction
    backSubtractor = 0;

    setDefaultParam();

    qDebug() << "Constructor End: Process";
}

Process::~Process()
{
    qDebug() << "Destructor Begin: Process";

    wait();

    cvReleaseImage(&hitResult);

    cvReleaseImage(&hitImage);
    cvReleaseImage(&grayImage);
    cvReleaseImage(&backImage);
    cvReleaseImage(&foreImage);

    cvReleaseMemStorage(&haarStorage);
    cvReleaseMemStorage(&contourStorage);
    cvReleaseMemStorage(&approxStorage);

    if (hullsStorage)
        cvReleaseMemStorage(&hullsStorage);

    if (backSubtractor)
        delete backSubtractor;

    qDebug() << "Destructor End: Process";
}

void Process::setDefaultParam()
{
    setMode(ProcessColor);

    // Color
    colorRangeMode = AllRange;
    colorRangeParam.invert = false;
    colorRangeParam.Hmin = 0;
    colorRangeParam.Hmax = 50;
    colorRangeParam.Smin = 50;
    colorRangeParam.Smax = 255;
    colorRangeParam.Vmin = 50;
    colorRangeParam.Vmax = 255;

    // Motion
    motionParam.sensitivity = 100;

    // Haar
    haarParam.scaleFactor = 1.1;
    haarParam.minSizeX = 120;
    haarParam.minSizeY = 120;
    haarParam.maxSizeX = 0;
    haarParam.maxSizeY = 0;
    //setHaarFile("haarcascades/haarcascade_frontalface_default.xml");

    // Contour
    contourParam.threshold1 = 10;
    contourParam.threshold2 = 100;

    // HoughCircles
    houghCirclesParam.inverseRatio = 5;
    houghCirclesParam.minDistance = 100;
    houghCirclesParam.param1 = 100;
    houghCirclesParam.param2 = 100;
    houghCirclesParam.minRadius = 0;
    houghCirclesParam.maxRadius = 0;

    // Subtraction
    subtractionImageParam.history = 15000;
    subtractionImageParam.varThreshold = 16;
    subtractionImageParam.bShadowDetection = false;

    subtractionImageData.commandStart = false;
    subtractionImageData.commandStop = false;
    subtractionImageData.commandChangeParam = false;

    subtractionHitData.isSubtraction = false;
    subtractionHitData.commandAddSeveral = 0;
    subtractionHitData.commandClear = false;

    // Filters
    filterHitParam.erodeIteration = 0;
    filterHitParam.dilateIteration = 0;

    // Areas & Sequences
    filterAreaParam.isFilterOutframe = false;
    seqAreaParam.count = 1;
    seqAreaParam.lenghtLimit = 1000;
    filterSeqAreaParam.buffSize = 0;

    seqAreas.resize(1);
    seqAreas[0].number = 0;
    seqAreasLast = &seqAreas;

    // Transform
    trans2D.mx = 0;
    trans2D.my = 0;
    trans2D.sx = 1;
    trans2D.sy = 1;
    trans2D.theta = 0;
    trans2D.g = 0;
    trans2D.h = 0;

    trans2D.deepHx = 0;
    trans2D.deepHy = width/2;
    trans2D.deepHs = 0.0;
}

void Process::step()
{
    QTime time;
    time.start();

    realizeCommands();

    switch (mode) {
    case ProcessNone:
        processSubtractionImage();
        processFiltersHit();
        break;

    case ProcessColor:
        findColor();
        processFiltersHit();
        findClusters(hitImage, areas);
        transform2DAreas(areas);
        filterAreas(areas);
        findSeqAreas(areas, seqAreas);
        filterSeqAreas(seqAreas, seqAreasBuffer);
        break;

    case ProcessMotion:
        findMotion();
        processFiltersHit();
        findClusters(hitImage, areas);
        transform2DAreas(areas);
        filterAreas(areas);
        findSeqAreas(areas, seqAreas);
        filterSeqAreas(seqAreas, seqAreasBuffer);
        cvCopy(image, prevImage);
        break;

    case ProcessHaar:
        findHaar();
        findSeqAreas(areas, seqAreas);
        filterSeqAreas(seqAreas, seqAreasBuffer);
        break;

    case ProcessContour:
        processContoursHit();
        processSubtractionHit();
        processFiltersHit();
        findContours();
        transform2DContours(contours);
        findClusters(hitImage, areas);
        transform2DAreas(areas);
        findSeqAreas(areas, seqAreas);
        filterSeqAreas(seqAreas, seqAreasBuffer);
        break;

    case ProcessHoughCircles:
        findHoughCircles();
        findSeqAreas(areas, seqAreas);
        filterSeqAreas(seqAreas, seqAreasBuffer);
        break;
    }

    timeMean += time.elapsed();
    timeNum++;
    if ( timeNum == 10 ) {
        timeResult = timeMean/10;
        timeMean = 0;
        timeNum = 0;
    }
}

void Process::copyData()
{
    if (image)
        cvCopy(image, imageResult);
    cvCopy(hitImage, hitResult);
    areasResult = areas;
    seqAreasResult = *seqAreasLast;
    contoursResult = contours;

    isUpdate = true;
}

void Process::setCommand(QString name)
{
    Command command;
    command.name = name;
    commands.push_back(command);
}

void Process::realizeCommands()
{
    for (unsigned int i=0; i<commands.size(); i++) {
        Command &command = commands.at(i);
        qDebug() << "Execute command:" << command.name;
        if (command.name == "SubtractionImageStart") {
            this->subtractionImageStart();
        }
        else if (command.name == "SubtractionImageStop") {
            this->subtractionImageStop();
        }
    }
    commands.clear();
}

void Process::setImage(IplImage *image)
{
    assert(image);
    assert(image->width == width && image->height == height);
    this->image = image;
}

void Process::setHaarFile(string file)
{
    wait();

    if ( file == "" )
        return;

    if (haarCascade) {
        cvReleaseHaarClassifierCascade(&haarCascade);
    }

    haarCascade = (CvHaarClassifierCascade *)cvLoad(file.c_str(), 0, 0, 0);
    if (!haarCascade)
        qDebug() << "Error open cascade file:" << QString(file.c_str());
    else
        qDebug() << "Open cascade file:" << QString(file.c_str());
}

void Process::setHaarParam(Process::HaarParam param)
{
    haarParam = param;
    if ( !(haarParam.scaleFactor > 1.01) ) {
        haarParam.scaleFactor = 1.1;
    }
}

void Process::setContourParam(Process::ContourParam param)
{
    contourParam = param;
}

void Process::setFilterAreaParam(Process::FilterAreaParam param)
{
    filterAreaParam = param;
}

void Process::setSeqAreaParam(Process::SeqAreaParam param)
{
    seqAreaParam = param;
    seqAreasBuffer.clear();
}

void Process::setFilterSeqAreaParam(Process::FilterSeqAreaParam param)
{
    filterSeqAreaParam = param;
}

void Process::run()
{
    step();
}

void Process::findColor()
{
    // Очищаем список структур Area от предыдущего использования
    areas.clear();

    // Поиск цветов и регионов
    int xStep = 1;

    for( int y=0; y<height; y+=1 ) {

        // Получаем указатели на начало строки 'y'
        uchar* img_ptr = (uchar*) (image->imageData + y * image->widthStep);
        uchar* hit_ptr = (uchar*) (hitImage->imageData + y * hitImage->widthStep);

        for( int x=0; x<width; x+=xStep ) {

            xStep = 1;
            hit_ptr[x] = 0;

            unsigned char r = img_ptr[3*x+2];
            unsigned char g = img_ptr[3*x+1];
            unsigned char b = img_ptr[3*x+0];

            int ss = r*256*256 + g*256 + b;

            /*
            Условие:
            if( i >= min && i <= max )
            Можно заменить таким:
            if( (u32)(i-min) <= (u32)max - min )
              */


            /* Проверка условия в человеко-понятной форме

            bool h = *((unsigned char *)(HTable + ss)) >= colorRangeParam.Hmin &&
                      *((unsigned char *)(HTable + ss)) <= colorRangeParam.Hmax;
            bool s = *((unsigned char *)(STable + ss)) >= colorRangeParam.Smin;
            bool v = *((unsigned char *)(VTable + ss)) >= colorRangeParam.Vmin;
            bool invert = colorRangeParam.invert;

            bool result = (h ^ invert) && v && s;

            */


            if (
                 (
                   (
                     *((unsigned char *)(HTable + ss)) >= colorRangeParam.Hmin
                     &&
                     *((unsigned char *)(HTable + ss)) <= colorRangeParam.Hmax
                   )
                   ^
                   colorRangeParam.invert
                 )
                 &&
                 *((unsigned char *)(STable + ss)) >= colorRangeParam.Smin
                 &&
                 *((unsigned char *)(VTable + ss)) >= colorRangeParam.Vmin
               )
            {
                hit_ptr[x] = 255;
                xStep = 1;
            }

        }
    }
}

void Process::findMotion()
{
    // Очищаем список структур Area от предыдущего использования
    areas.clear();

    for( int y=0; y<height; y+=1 ) {

        // Получаем указатели на начало строки 'y'
        uchar* img_ptr = (uchar*) (image->imageData + y * image->widthStep);
        uchar* prv_img_ptr = (uchar*) (prevImage->imageData + y * image->widthStep);
        uchar* hit_ptr = (uchar*) (hitImage->imageData + y * hitImage->widthStep);

        for( int x=0; x<width; x+=1 ) {

            hit_ptr[x] = 0;

            //uchar a = rgb2gray(img_ptr[3*x+2], img_ptr[3*x+1], img_ptr[3*x+0]);
            //uchar b = rgb2gray(prv_img_ptr[3*x+2], prv_img_ptr[3*x+1], prv_img_ptr[3*x+0]);

            int dr = abs(img_ptr[3*x+2] - prv_img_ptr[3*x+2]);
            int dg = abs(img_ptr[3*x+1] - prv_img_ptr[3*x+1]);
            int db = abs(img_ptr[3*x+0] - prv_img_ptr[3*x+0]);

            if ( dr+dg+db > motionParam.sensitivity ) {
                hit_ptr[x] = 255;
            }
        }
    }
}

void Process::findSeqAreas(Areas &areas, SeqAreas &seqAreas)
{
    // ===========================================
    // Исходные данные

    // areas - новые найденые регионы
    // seqAreas - итоговый массив

    // Определим, сколько линий нам нужно
    unsigned int seqN = seqAreaParam.count;

    // Сколько новых регионов найдено
    unsigned int areaN = areas.size();

    // Чтобы избежать ошибок, будем проверять размер вектора,
    // хранящего все линии, в начале работы
    if ( seqAreas.size() != seqN )
        seqAreas.resize(seqN);

    // Создаем двумерную матрицу, в которой просчитаем все расстояния
    // от новых точек до предыдущих
    double m[areaN][seqN];

    // Отмечаем в массиве, если одна линия не имеет элементов
    bool newMat[seqN];
    // Отмечаем, если новые точки использованы
    bool useNewAreaMat[areaN];

    for (unsigned int i=0; i<areaN; i++) {
        useNewAreaMat[i] = false;
    }

    // Отмечаем использованные линии
    bool useOldSeqAreaMat[seqN];

    // ===========================================

    // Просчитываем расстояния от последних точек линии
    // до новых точек
    for (unsigned int j=0; j<seqN; j++) {

        // Просто инициализируем для будущего применения
        useOldSeqAreaMat[j] = false;

        newMat[j] = false;      // Инициализируем

        //if (seqAreas.at(j).isBreak) {
        if ( seqAreas.at(j).number == 0 ) {
            // Эта последовательность пуста, помечаем как новую
            // В дальнейшем выберем для этой линии свободную новую
            // точку
            newMat[j] = true;
        }
        else {
            // Пока считаем, что не найдено ни одной последовательности
            //seqAreas.at(j).isBreak = true;
            //seqAreas.at(j).number = 0;

            // Обходим все новые точки
            for (unsigned int i=0; i<areaN; i++) {
                // Расчитываем расстояние
                m[i][j] = length(areas.at(i).pt, seqAreas.at(j).pt);
            }

        }
    }

    // Будем просматривать массив m пока не найдем всевозможные
    // подходящие последовательности
    bool isFind = true;
    while (isFind) {
        isFind = false;
        double rMin = 10000;
        unsigned int iMin = 0;
        unsigned int jMin = 0;

        // Поиск минимума
        for (unsigned int i=0; i<areaN; i++)
            for (unsigned int j=0; j<seqN; j++) {
                if ( !newMat[j] && !useNewAreaMat[i] && !useOldSeqAreaMat[j] ) {
                    if (m[i][j]<rMin && m[i][j] < seqAreaParam.lenghtLimit ) {
                        isFind = true;
                        rMin = m[i][j];
                        iMin = i;
                        jMin = j;
                    }
                }
            }

        if (isFind) {
            SeqArea newArea;
            // seqOldAreas.at(jMin) содержит правильные данные!
            newArea.number = seqAreas.at(jMin).number + 1;
            newArea.isUsed = false;
            newArea.pt[0] = areas.at(iMin).pt[0];
            newArea.pt[1] = areas.at(iMin).pt[1];
            newArea.ptReal[0] = areas.at(iMin).ptReal[0];
            newArea.ptReal[1] = areas.at(iMin).ptReal[1];

            newArea.ptPrev[0] = seqAreas.at(jMin).pt[0];
            newArea.ptPrev[1] = seqAreas.at(jMin).pt[1];
            newArea.ptPrevReal[0] = seqAreas.at(jMin).ptReal[0];
            newArea.ptPrevReal[1] = seqAreas.at(jMin).ptReal[1];

            newArea.width  = areas.at(iMin).width;
            newArea.height = areas.at(iMin).height;
            newArea.widthReal  = areas.at(iMin).width;
            newArea.heightReal = areas.at(iMin).height;
            newArea.length = m[iMin][jMin];

            // Найдем угол линии с предыдущей точкой
            newArea.angle = angle(seqAreas.at(jMin).pt, newArea.pt);

            seqAreas[jMin] = newArea;

            useNewAreaMat[iMin] = true;
            useOldSeqAreaMat[jMin] = true;
        }
    }

    // Финальная обработка
    for (unsigned int j=0; j<seqN; j++) {

        // Если линии только начались, заполняем их любыми свободными
        // новыми точками
        if (newMat[j]) {
            for (unsigned int i=0; i<areaN; i++) {
                if (!useNewAreaMat[i] && newMat[j]) {
                    SeqArea newArea;
                    newArea.number = 1;
                    newArea.isUsed = false;
                    newArea.pt[0] = areas.at(i).pt[0];
                    newArea.pt[1] = areas.at(i).pt[1];
                    newArea.ptReal[0] = areas.at(i).ptReal[0];
                    newArea.ptReal[1] = areas.at(i).ptReal[1];

                    newArea.width = areas.at(i).width;
                    newArea.height = areas.at(i).height;
                    newArea.length = 0;
                    newArea.angle = 0;

                    seqAreas[j] = newArea;

                    useNewAreaMat[i] = true;
                    useOldSeqAreaMat[j] = true;
                    newMat[j] = false;
                }
            }
        }

        if (useOldSeqAreaMat[j] == false) {
            seqAreas[j].number = 0;
        }

    }

    // Предпологаем, что результат будет в seqAreasLast,
    // если, например, не будет применено сглаживание
    seqAreasLast = &seqAreas;
}

void Process::filterAreas(Areas &areas)
{
    // С производительностью нужно что-то делать...
    if (filterAreaParam.isFilterOutframe) {
        Areas oldAreas = areas;
        areas.clear();

        for (unsigned int i=0; i<oldAreas.size(); i++) {
            if (oldAreas.at(i).pt[0] <= width  && oldAreas.at(i).pt[0] >= 0 &&
                oldAreas.at(i).pt[1] <= height && oldAreas.at(i).pt[1] >= 0 ) {
                areas.push_back(oldAreas.at(i));
            }
        }
    }
}

void Process::filterSeqAreas(SeqAreas &seqAreas, SeqAreasBuffer &seqAreasBuffer)
{
    if ( filterSeqAreaParam.buffSize == 0 )
        return;

    seqAreasBuffer.push_back(seqAreas);

    if ( seqAreasBuffer.size() < filterSeqAreaParam.buffSize*2+1 ) {
        // Заполняем буфер пустыми значениями

        SeqAreas &last = seqAreasBuffer.back();
        for ( unsigned int i = 0; i < last.size(); i++) {
            last[i].number = 0;
        }

        seqAreas = seqAreasBuffer.back();
        return;
    }

    while ( seqAreasBuffer.size() > filterSeqAreaParam.buffSize*2+1 ) {
        // Удаляем лишнее из буфера
        seqAreasBuffer.pop_front();
    }

    switch(filterSeqAreaParam.buffSize) {
    case 1:
        for (unsigned int i = 0; i < seqAreas.size(); i++) {

            SeqArea &prev = seqAreasBuffer.at(0).at(i);
            SeqArea &curr = seqAreasBuffer.at(1)[i];
            SeqArea &next = seqAreasBuffer.at(2)[i];

            //qDebug() << "!!" << prev.number << curr.number << next.number;

            // Устранение всплесков
            if (prev.number == 0 && next.number == 0)
            {
                curr.number = 0;
            }

            // Устранение пропусков
            if (prev.number > 0 && curr.number == 0 && next.number > 0)
            {
                curr.number = prev.number + 1;
                curr.pt[0] = ( prev.pt[0] + next.pt[0] ) / 2;
                curr.pt[1] = ( prev.pt[1] + next.pt[1] ) / 2;
                curr.ptReal[0] = ( prev.ptReal[0] + next.ptReal[0] ) / 2;
                curr.ptReal[1] = ( prev.ptReal[1] + next.ptReal[1] ) / 2;

                curr.width = ( prev.width + next.width ) / 2;
                curr.height = ( prev.height + next.height ) / 2;
                curr.widthReal = ( prev.widthReal + next.widthReal ) / 2;
                curr.heightReal = ( prev.heightReal + next.heightReal ) / 2;

                curr.length = ( prev.length + next.length ) / 2;
                curr.angle = ( prev.angle + next.angle ) / 2;

                next.number = curr.number + 1;
                next.ptPrev[0] = curr.pt[0];
                next.ptPrev[1] = curr.pt[1];
                next.ptPrevReal[0] = curr.ptPrevReal[0];
                next.ptPrevReal[1] = curr.ptPrevReal[1];
            }


            // Сглаживание
            if ( prev.number > 0 && curr.number > 0 && next.number > 0)
            {
                curr.pt[0] = ( prev.pt[0] + curr.pt[0] + next.pt[0] ) / 3;
                curr.pt[1] = ( prev.pt[1] + curr.pt[1] + next.pt[1] ) / 3;
                curr.ptReal[0] = ( prev.ptReal[0] + curr.ptReal[0] + next.ptReal[0] ) / 3;
                curr.ptReal[1] = ( prev.ptReal[1] + curr.ptReal[1] + next.ptReal[1] ) / 3;

                curr.width = ( prev.width + curr.width + next.width ) / 3;
                curr.height = ( prev.height + curr.height + next.height ) / 3;
                curr.widthReal = ( prev.widthReal + curr.widthReal + next.widthReal ) / 3;
                curr.heightReal = ( prev.heightReal + curr.heightReal + next.heightReal ) / 3;
            }

        }

        //qDebug() << temp << seqAreas[0].number << seqAreas.size();
        seqAreas = seqAreasBuffer.back();
        seqAreasLast = &seqAreasBuffer.at(1);
        break;

    }
}


void Process::findHaar()
{
    if (!haarCascade)
        return;

    cvClearMemStorage(haarStorage);

    cvCvtColor(image, grayImage, CV_RGB2GRAY);

    CvSeq *seq = cvHaarDetectObjects(grayImage, haarCascade, haarStorage,
                                     haarParam.scaleFactor, 3, CV_HAAR_DO_CANNY_PRUNING,
                                     cvSize(haarParam.minSizeX, haarParam.minSizeY),
                                     cvSize(haarParam.maxSizeX, haarParam.maxSizeY));
    areas.clear();

    for (int i=0; i<seq->total; i++) {
        CvRect *rect = (CvRect *)cvGetSeqElem(seq, i);
        Area area;
        area.pt[0] = rect->x + rect->width/2;
        area.pt[1] = rect->y + rect->height/2;
        area.width = rect->width;
        area.height = rect->height;
        areas.push_back(area);
    }
}

void Process::processContoursHit()
{
    cvCvtColor(image, grayImage, CV_RGB2GRAY);

//    if (param.contour.smooth) {
//        cvSmooth(grayImage, grayImage, CV_BLUR, 3, 3);
//    }

    cvCanny(grayImage, hitImage, contourParam.threshold1, contourParam.threshold2, 3);
}


void Process::findContours()
{
    cvClearMemStorage(contourStorage);
    contours.clear();

    // находим контуры
    cvFindContours(hitImage, contourStorage, &contoursSeq, sizeof(CvContour),
                   CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    for(CvSeq* seq = contoursSeq; seq != 0; seq = seq->h_next) {
        //CvSeq* approxSeq = cvApproxChains(seq, approxStorage, CV_CHAIN_APPROX_SIMPLE);

        Contour contour;
        for( int i=0; i<seq->total; ++i ) {
            CvPoint* cvP = (CvPoint*)cvGetSeqElem(seq, i);
            ContourPt pt;
            pt.x = cvP->x;
            pt.y = cvP->y;
            contour.push_back(pt);
            //qDebug() << cvP->x << cvP->y;
        }
        contours.push_back(contour);        
    }

    // пример работы с контуром
    //for(CvSeq* seq = contours; seq != 0; seq = seq->h_next){
        // нарисовать контур
        // cvDrawContours(dstImage, seq, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8);
        // Работаем с точками последовательности
         //CvPoint* p = (CvPoint*)cvGetSeqElem ( seq, i );
    //}

    // рисуем обводку
//    if (param.contour.isDrawHull) {
//        CvMemStorage* hullStorage = cvCreateMemStorage(0);

//        for(CvSeq* seq = contours; seq != 0; seq = seq->h_next){
//            CvSeq *hulls = cvConvexHull2(seq, hullStorage, CV_CLOCKWISE, 1);
//            //cvDrawContours(dstImage, hulls, CV_RGB(255, 0, 0), CV_RGB(100, 0, 0), 0, 2, 8);

//            cvClearMemStorage(hullStorage);
//        }

//        cvReleaseMemStorage(&hullStorage);
    //    }

}

void Process::findHulls()
{
    if (hullsStorage)
        cvReleaseMemStorage(&hullsStorage);

    hullsStorage = cvCreateMemStorage(0);

    bool isFirst =  true;
    CvSeq *curHulls = NULL;
    hullsSeq = NULL;

    for(CvSeq* seq = contoursSeq; seq != 0; seq = seq->h_next){

        if (! (seq->flags & CV_SEQ_FLAG_HOLE))
        {

            if (isFirst) {
                isFirst = false;
                hullsSeq = cvConvexHull2(seq, hullsStorage, CV_CLOCKWISE, 1);
                curHulls = hullsSeq;
            }
            else {
                curHulls->h_next = cvConvexHull2(seq, hullsStorage, CV_CLOCKWISE, 1);
                curHulls = curHulls->h_next;

            }

        }
    }
}

void Process::findHoughCircles()
{
    cvClearMemStorage(houghCirclesStorage);

    cvCvtColor(image, grayImage, CV_RGB2GRAY);

    cvSmooth(grayImage, grayImage, CV_GAUSSIAN, 5, 5 );

    CvSeq* seq = cvHoughCircles(
            grayImage,
            houghCirclesStorage,
            CV_HOUGH_GRADIENT,
            houghCirclesParam.inverseRatio,
            houghCirclesParam.minDistance,
            houghCirclesParam.param1,
            houghCirclesParam.param2,
            houghCirclesParam.minRadius,
            houghCirclesParam.maxRadius
            );

    areas.clear();
    for (int i=0; i<seq->total; i++) {
        float* p = (float*) cvGetSeqElem( seq, i );
        Area area;
        area.pt[0] = p[0];
        area.pt[1] = p[1];
        area.width = p[2];
        area.height = p[2];
        areas.push_back(area);
    }

}

void Process::processSubtractionImage()
{
    if ( subtractionImageData.commandStop ) {
        if (backSubtractor) {
            delete backSubtractor;
            backSubtractor = 0;
        }
        cvSet(hitImage, cvScalar(0));
        subtractionImageData.commandStop = false;
    }

    if ( subtractionImageData.commandStart ) {
        if (backSubtractor)
            delete backSubtractor;
        backSubtractor = new
                cv::BackgroundSubtractorMOG2(subtractionImageParam.history,
                                             subtractionImageParam.varThreshold,
                                             subtractionImageParam.bShadowDetection);
        subtractionImageData.commandStart = false;
    }

    if (backSubtractor) {
        cv::Mat frame(image);
        cv::Mat fore(hitImage);
        cv::Mat back(backImage);
        backSubtractor->operator ()(frame, fore);
        backSubtractor->getBackgroundImage(back);
    }
}

void Process::processSubtractionHit()
{
    if ( subtractionHitData.commandClear ) {
        cvSet(hitSubImage, cvScalar(0));
        subtractionHitData.commandClear = false;
        subtractionHitData.isSubtraction = false;
    }

    if ( subtractionHitData.commandAddSeveral > 0 ) {
        cvSet(hitSubImage, cvScalar(1), hitImage);
        subtractionHitData.commandAddSeveral -= 1;
        subtractionHitData.isSubtraction = true;
    }

    if ( subtractionHitData.isSubtraction ) {
        cvSet(hitImage, cvScalar(0), hitSubImage);
    }
}

void Process::processFiltersHit()
{
    if (filterHitParam.erodeIteration) {
        cvErode(hitImage, grayImage, 0, filterHitParam.erodeIteration);
        cvCopy(grayImage, hitImage);
    }

    if (filterHitParam.dilateIteration) {
        cvDilate(hitImage, grayImage, 0, filterHitParam.dilateIteration);
        cvCopy(grayImage, hitImage);
    }
}

void Process::transform2DAreas(Areas &areas)
{
    vector<Area>::iterator it = areas.begin();
    for (; it != areas.end(); ++it) {
        Area &area = *it;
        transform2DArea(area);
    }
}

void Process::transform2DArea(Area &area)
{
    transform2DContrary(area.ptReal[0], area.ptReal[1], area.pt[0], area.pt[1]);
    area.width = area.widthReal/trans2D.sx;
    area.height = area.heightReal/trans2D.sy;
    area.height -= area.height * (trans2D.deepHx - area.ptReal[0]) * trans2D.deepHs;
}

void Process::transform2DContours(Contours &contours)
{
    vector<Contour>::iterator it = contours.begin();
    for (; it != contours.end(); ++it) {
        Contour &contour = *it;
        transform2DContour(contour);
    }
}

void Process::transform2DContour(Contour &contour)
{
    vector<ContourPt>::iterator it = contour.begin();
    for (; it != contour.end(); ++it) {
        ContourPt &contourPt = *it;
        contourPt.xReal = contourPt.x;
        contourPt.yReal = contourPt.y;
        transform2DContrary(contourPt.xReal, contourPt.yReal, contourPt.x, contourPt.y);
    }
}

/*
 *  qx    ( 1      0      mx )   ( px )
 *  qy  = ( 0      1      my ) * ( py )
 *  1     ( 0      0      1  )   ( 1  )
 *
 *  qx    ( sx     0      0 )   ( px )
 *  qy  = ( 0      sy     0 ) * ( py )
 *  1     ( 0      0      1 )   ( 1  )
 *
 *  qx    ( cos(theta)   -sin(theta)     0 )   ( px )
 *  qy  = ( sin(theta)    cos(theta)     0 ) * ( py )
 *  1     ( 0             0              1 )   ( 1  )
 *
 *  qx    ( 1      h      0 )   ( px )
 *  qy  = ( 0      1      0 ) * ( py )
 *  1     ( 0      0      1 )   ( 1  )
 *
 *  qx    ( 1      0      0 )   ( px )
 *  qy  = ( g      1      0 ) * ( py )
 *  1     ( 0      0      1 )   ( 1  )
 *
 */
void Process::transform2D(int px, int py, int &qx, int &qy)
{
    qx = trans2D.sx * px;
    qy = trans2D.sy * py;

    qx = qx + trans2D.mx;
    qy = qy + trans2D.my;

    qx = qx + trans2D.h * qy;
    //qy = qy;

    //qx = qx;
    qy = trans2D.g * qx + qy;

    int qxTemp = cos(trans2D.theta) * qx + -sin(trans2D.theta) * qy;
    qy         = sin(trans2D.theta) * qx +  cos(trans2D.theta) * qy;
    qx = qxTemp;

    qy = qy - (trans2D.deepHy - qy) * (trans2D.deepHx - qx) * trans2D.deepHs;

}

/*
 *  qx    ( 1      0     -mx )   ( px )
 *  qy  = ( 0      1     -my ) * ( py )
 *  1     ( 0      0      1  )   ( 1  )
 *
 *  qx    ( 1/sx   0      0 )   ( px )
 *  qy  = ( 0      1/sy   0 ) * ( py )
 *  1     ( 0      0      1 )   ( 1  )
 *
 *  qx    (  cos(theta)   sin(theta)     0 )   ( px )
 *  qy  = ( -sin(theta)   cos(theta)     0 ) * ( py )
 *  1     (  0            0              1 )   ( 1  )
 *
 *  qx    ( 1     -h      0 )   ( px )
 *  qy  = ( 0      1      0 ) * ( py )
 *  1     ( 0      0      1 )   ( 1  )
 *
 *  qx    (  1      0      0 )   ( px )
 *  qy  = ( -g      1      0 ) * ( py )
 *  1     (  0      0      1 )   ( 1  )
 *
 */
void Process::transform2DContrary(int px, int py, int &qx, int &qy)
{
    qx = px;
    qy = py;

    //qy = qy - (trans2D.deepHy - qy) * (trans2D.deepHx - qx) / trans2D.deepHs;

    qy = ( qy + trans2D.deepHy*(trans2D.deepHx - qx)*trans2D.deepHs ) /
         (  1 +                (trans2D.deepHx - qx)*trans2D.deepHs );

    int qx1 =  cos(trans2D.theta) * qx + sin(trans2D.theta) * qy;
    int qy1 = -sin(trans2D.theta) * qx + cos(trans2D.theta) * qy;
    qx = qx1;
    qy = qy1;

    qx = qx;
    qy = -trans2D.g * qx + qy;

    qx = qx - trans2D.h * qy;
    qy = qy;

    qx = qx - trans2D.mx;
    qy = qy - trans2D.my;

    qx = qx / trans2D.sx;
    qy = qy / trans2D.sy;
}


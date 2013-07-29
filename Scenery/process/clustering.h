#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <opencv/cxcore.h>
#include "processdata.h"

class Clustering
{
public:
    Clustering();
    ~Clustering();

    void findClusters(IplImage *hit, Areas &areas);

    enum ClusterMode {
        ClusterNone,
        ClusterSimple,
        ClusterTable
    };

    void setClusterMode(ClusterMode mode) { clusterMode = mode; }

    struct SimpleClusterParam {
        int distance; // Расстояние между соседними точками и регионами,
                      // чтобы образовать один регион
        int limit;    // Минимальное кол-во пикселей в регионе
        int density;  // Минимальная плотность точек в регионе
    };

    void setSimpleClusterParam(SimpleClusterParam param);

    struct TableClusterParam {
        int cellWidth;   // Ширина и высота ячеек, на которые разобъется изображение
        int cellHeight;
        int density;     // Минимальная плотность точек в регионе
    };

    void setTableClusterParam(TableClusterParam param);

private:
    // ===============================================================

    ClusterMode clusterMode;

    SimpleClusterParam simpleClusterParam;

    // Регион, который соответствует определенному параметру
    struct CvArea {
        CvPoint pt;

        CvPoint pt1;
        CvPoint pt2;

        int n;          // Количество точек в этом регионе
        int p;          // Плотность точек в процентах

        CvArea *next;
    };

    CvArea *firstArea;

    void simpleClustering(IplImage *hit, Areas &areas);

    // Обрабатываем точку, как новую часть региона,
    // заносим сырые данные о регионах в CvArea
    void findAreas(int x, int y);

    // Объединяем регионы CvArea, убираем ненужные
    // и конвертируем CvArea в Area
    void filterAreas(Areas &areas);

    // Очищаем список структур CvArea
    void clearCvAreas();

    // ===============================================================
    TableClusterParam tableClusterParam;

    void tableClustering(IplImage *hit, Areas &areas);

};

#endif // CLUSTERING_H

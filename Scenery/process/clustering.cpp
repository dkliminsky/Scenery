#include "clustering.h"
#include <QDebug>

Clustering::Clustering()
{
    firstArea = NULL;

    clusterMode = ClusterNone;

    simpleClusterParam.distance = 1;
    simpleClusterParam.limit = 5;
    simpleClusterParam.density = 0;

    tableClusterParam.cellHeight = 5;
    tableClusterParam.cellWidth = 5;
    tableClusterParam.density = 50;
}

Clustering::~Clustering()
{
    void clearCvAreas();
}

void Clustering::findClusters(IplImage *hit, Areas &areas)
{
    switch(clusterMode) {
    case ClusterNone:
        break;
    case ClusterSimple:
        simpleClustering(hit, areas);
        break;
    case ClusterTable:
        tableClustering(hit, areas);
        break;
    }
}

void Clustering::setSimpleClusterParam(Clustering::SimpleClusterParam param)
{
    simpleClusterParam = param;
    if ( simpleClusterParam.distance < 1 ) simpleClusterParam.distance = 1;
}

void Clustering::setTableClusterParam(Clustering::TableClusterParam param)
{
    tableClusterParam = param;
    if ( tableClusterParam.cellWidth < 1 ) tableClusterParam.cellWidth = 1;
    if ( tableClusterParam.cellHeight < 1 ) tableClusterParam.cellHeight = 1;
}

void Clustering::simpleClustering(IplImage *hit, Areas &areas)
{
    // Очищаем список структур Area от предыдущего использования
    areas.clear();
    clearCvAreas();

    for( int y=0; y<hit->height; y++ ) {

        // Получаем указатели на начало строки 'y'
        uchar* hit_ptr = (uchar*) (hit->imageData + y * hit->widthStep);

        for( int x=0; x<hit->width; x++ ) {
            if ( hit_ptr[x] )
            {
                findAreas(x, y);
            }

        }
    }

    // Объединяем рядом стоящие регионы
    // и убираем не нужные
    filterAreas(areas);
}

void Clustering::findAreas(int x, int y)
{
    CvArea *a = firstArea;

    // проверяем все регионы, пока не найдем подходящий
    while ( a!=NULL ) {

        // Проверка попадания текущей точки в существующий регион с учетом simpleClusterParam.distance
        if ( x >= a->pt1.x - simpleClusterParam.distance - 1 && x <= a->pt2.x + simpleClusterParam.distance + 1 &&
             y >= a->pt1.y - simpleClusterParam.distance - 1 && y <= a->pt2.y + simpleClusterParam.distance + 1 )
        {
            a->n++;
            if (x < a->pt1.x) a->pt1.x = x;
            else if (x > a->pt2.x) a->pt2.x = x;

            // Эта проверка не нужна, т.к. при последовательном
            // обходе пикселей регионов выше y не существует
            // if (y < a->pt1.y) a->pt1.y = y;

            if (y > a->pt2.y) a->pt2.y = y;

            return;
        }

        a = a->next;
    }

    // Если подходящий регион не был найден,
    // создаем новый регион
    a = new CvArea;
    a->n = 1;
    a->pt1.x = x;
    a->pt1.y = y;
    a->pt2.x = x;
    a->pt2.y = y;
    a->next = firstArea;
    firstArea = a;
}

void Clustering::filterAreas(Areas &areas)
{
    // Объединяем все регионы, которые находятся в пределах range
    CvArea *a1 = firstArea;
    while (a1!=NULL) {
        CvArea *a2 = firstArea;
        while (a2!=NULL) {
            bool isFound = false;

            if ( a1!=a2 && a1->n > 0 && a2->n > 0) {
                if ( a2->pt1.x >= a1->pt1.x - simpleClusterParam.distance - 1 &&
                     a2->pt1.x <= a1->pt2.x + simpleClusterParam.distance + 1 &&
                     a2->pt2.y >= a1->pt1.y - simpleClusterParam.distance - 1 &&
                     a2->pt2.y <= a1->pt2.y + simpleClusterParam.distance + 1)
                {
                    a1->n+=a2->n;

                    if ( a2->pt2.x > a1->pt2.x ) a1->pt2.x = a2->pt2.x;
                    if ( a2->pt1.y < a1->pt1.y ) a1->pt1.y = a2->pt1.y;

                    a2->n = 0;
                    isFound = true;
                }
                if ( a2->pt2.x >= a1->pt1.x - simpleClusterParam.distance - 1 &&
                     a2->pt2.x <= a1->pt2.x + simpleClusterParam.distance + 1 &&
                     a2->pt2.y >= a1->pt1.y - simpleClusterParam.distance - 1 &&
                     a2->pt2.y <= a1->pt2.y + simpleClusterParam.distance + 1)
                {
                    a1->n+=a2->n;

                    if ( a2->pt1.x < a1->pt1.x ) a1->pt1.x = a2->pt1.x;
                    if ( a2->pt1.y < a1->pt1.y ) a1->pt1.y = a2->pt1.y;

                    a2->n = 0;
                    isFound = true;
                }

                if (a2->pt1.x >= a1->pt1.x && a2->pt2.x <= a1->pt2.x &&
                    a2->pt1.y >+ a1->pt1.y && a2->pt1.y <= a1->pt2.y)
                {
                    a1->n+=a2->n;

                    if (a2->pt2.y > a1->pt2.y) a1->pt2.y = a2->pt2.y;

                    a2->n = 0;
                    isFound = true;
                }


            }

            if (isFound) {
                // Начнем проверку заново
                a2 = firstArea;
            }
            else {
                a2 = a2->next;
            }

        }
        a1 = a1->next;
    }

    // Убираем пустые и неподходящие регионы
    CvArea *a = firstArea;
    CvArea *newAreaFirst = NULL;
    while (a!=NULL) {

        // Фильтрация региона на количество точек и плотность точек
        if ( a->n < simpleClusterParam.limit ) {
            a->n=0;
        }
        else {
            // Подсчет плотности найденных точек в процентах
            a->p = int( double(a->n) / double((a->pt2.x - a->pt1.x + 1) * (a->pt2.y - a->pt1.y + 1)) * 100);

            // Здесь нужно учесть ситуацию, когда нужная нам область была объединена
            // с большой областью, в которой низкая плотность точек. Тогда у нужной нам область
            // будет низкая плотность точек и эта область исчезнет. Нужно дописать
            // алгоритм, находящий в этом регионе нужную плотность точек
            if (a->p < simpleClusterParam.density) a->n=0;
        }

        // Создаем новый список регионов, оставляя только нужные
        CvArea *areaTemp = a;
        a = a->next;

        if (areaTemp->n > 0) {
            // Формируем окончательный список
            areaTemp->next = newAreaFirst;
            newAreaFirst = areaTemp;

            // И еще посчитаем центральную точку
            areaTemp->pt.x = areaTemp->pt1.x + (areaTemp->pt2.x - areaTemp->pt1.x)/2;
            areaTemp->pt.y = areaTemp->pt1.y + (areaTemp->pt2.y - areaTemp->pt1.y)/2;

            // Дополнительно создаем STL список
            Area area;
            area.ptReal[0] = areaTemp->pt.x;
            area.ptReal[1] = areaTemp->pt.y;
            area.widthReal  = areaTemp->pt2.x - areaTemp->pt1.x;
            area.heightReal = areaTemp->pt2.y - areaTemp->pt1.y;
            areas.push_back(area);
        }
        else {
            delete areaTemp;
        }
    }

    firstArea = newAreaFirst;
}

void Clustering::clearCvAreas()
{
    CvArea *areaTemp;
    while (firstArea!=NULL) {
        areaTemp = firstArea;
        firstArea = firstArea->next;
        delete areaTemp;
    }
}

void Clustering::tableClustering(IplImage *hit, Areas &areas)
{
    areas.clear();
    int cellX = tableClusterParam.cellWidth;
    int cellY = tableClusterParam.cellHeight;
    int density = tableClusterParam.density;

    for (int i=0; i<hit->width/cellX; i++)
        for (int j=0; j<hit->height/cellY; j++)
        {
            int n = 0;
            for( int y=j*cellY; y<j*cellY+cellY; y++ ) {
                uchar* hit_ptr = (uchar*) (hit->imageData + y * hit->widthStep);
                for( int x=i*cellX; x<i*cellX+cellX; x++ ) {
                    if ( hit_ptr[x] )
                    {
                        n++;
                    }
                }
            }
            if ( n > 0 && (float)n/(float)(cellX*cellY)*100.0 >= density ) {
                Area area;
                area.ptReal[0] = i*cellX + cellX/2;
                area.ptReal[1] = j*cellY + cellY/2;
                area.widthReal  = cellX;
                area.heightReal = cellY;
                areas.push_back(area);
            }

        }
}

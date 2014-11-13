#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

// __FUNCTION__ __LINE__ __FILE__ typeid(this).name()
#define METHOD_BEGIN qDebug() << "BEGIN:" << __FUNCTION__ ;
#define METHOD_END   qDebug() << "  END:" << __FUNCTION__ ;

#endif // DEBUG_H

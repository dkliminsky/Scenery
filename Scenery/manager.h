#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "graphics/view.h"

#include "graphics/sscene.h"

#include "scenes/skeleton.h"
#include "scenes/cage.h"
//#include "scenes/strings.h"
//#include "scenes/brush.h"
//#include "scenes/inking.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

protected:
    void timerEvent(QTimerEvent *);

private:
    View *view;

signals:
    
public slots:
    
};

#endif // MANAGER_H

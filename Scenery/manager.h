#ifndef MANAGER_H
#define MANAGER_H

#include <QThread>
#include <QTime>
#include <QVector>

#include "process/process.h"
#include "process/input.h"
#include "process/gui/processwindow.h"
#include "process/gui/debugwindow.h"
#include "graphics/view.h"

#include "scenes/skeleton.h"
#include "scenes/cage.h"
#include "scenes/brush.h"
#include "scenes/strings.h"

typedef QVector<Process *> Processes;
typedef QVector<Input *>   Inputs;
typedef QVector<Scene *>   Scenes;

class Manager: public QObject
{
    Q_OBJECT

public:
    explicit Manager();
    ~Manager();

    Processes &getProcesses() { return processes; }
    Inputs    &getInputs()    { return inputs; }
    Scenes    &getScenes()    { return scenes; }
    View      *getView()      { return view; }

    void setScene(int n);
    void setPlay(bool play) { isPlay = play; }
    void step();

private:
    Processes processes;
    Inputs inputs;
    Scenes scenes;

    int curScene;

    View *view;
    ProcessWindow *processWindow;
    DebugWindow *debug;

    bool isPlay;
    void timerEvent(QTimerEvent *);
    bool firstInput;
    bool firstProcess;
signals:

public slots:

};

#endif // MANAGER_H

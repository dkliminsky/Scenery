QT += widgets opengl network

TARGET = Scenery
TEMPLATE = app

win32:INCLUDEPATH += c:/opencv/include
win32:LIBS += c:/opencv/lib/*.a

unix:LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so

CONFIG += c++11

HEADERS += \
    gui/mainwindow.h \
    gui/nodeitem.h \
    nodes/node.h \
    nodes/manager.h \
    nodes/opencv/cameranode.h \
    nodes/opencv/debugnode.h \
    debug.h \
    nodes/opencv/colornode.h \
    gui/linkitem.h \
    nodes/graphics/iscene.h \
    nodes/graphics/graphic.h \
    nodes/graphics/scene.h \
    nodes/graphics/tools.h \
    nodes/graphics/elements/color.h \
    nodes/graphics/elements/image.h \
    nodes/graphics/elements/point.h \
    nodes/graphics/threads/loadimagethread.h \
    nodes/graphics/threads/saveimagethread.h \
    nodes/graphics/viewnode.h \
    scenes/defaultscene.h \
    nodes/controls/controlbool.h \
    nodes/controls/controlbutton.h \
    nodes/controls/controlcolor.h \
    nodes/controls/controldouble.h \
    nodes/controls/controlimage.h \
    nodes/controls/controlint.h \
    nodes/controls/controlstring.h \
    nodes/controls/icontrol.h \
    nodes/nodes.h \
    scenes/examplemanager.h

SOURCES += \
    gui/mainwindow.cpp \
    gui/nodeitem.cpp \
    nodes/node.cpp \
    nodes/manager.cpp \
    main.cpp \
    nodes/opencv/cameranode.cpp \
    nodes/opencv/debugnode.cpp \
    nodes/opencv/colornode.cpp \
    gui/linkitem.cpp \
    nodes/graphics/graphic.cpp \
    nodes/graphics/scene.cpp \
    nodes/graphics/tools.cpp \
    nodes/graphics/elements/color.cpp \
    nodes/graphics/elements/image.cpp \
    nodes/graphics/elements/point.cpp \
    nodes/graphics/threads/loadimagethread.cpp \
    nodes/graphics/threads/saveimagethread.cpp \
    nodes/graphics/viewnode.cpp \
    scenes/defaultscene.cpp \
    nodes/controls/controlbool.cpp \
    nodes/controls/controlbutton.cpp \
    nodes/controls/controlcolor.cpp \
    nodes/controls/controldouble.cpp \
    nodes/controls/controlimage.cpp \
    nodes/controls/controlint.cpp \
    nodes/controls/controlstring.cpp \
    scenes/examplemanager.cpp

RESOURCES += \
icons.qrc

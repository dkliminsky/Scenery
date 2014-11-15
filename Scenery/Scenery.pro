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
    process/node.h \
    manager.h \
    process/opencv/cameranode.h \
    process/process.h \
    process/opencv/debugnode.h \
    debug.h \
    process/opencv/colornode.h \
    gui/linkitem.h \
    process/graphics/iscene.h \
    process/graphics/graphic.h \
    process/graphics/scene.h \
    process/graphics/tools.h \
    process/graphics/elements/color.h \
    process/graphics/elements/image.h \
    process/graphics/elements/point.h \
    process/graphics/threads/loadimagethread.h \
    process/graphics/threads/saveimagethread.h \
    process/graphics/viewnode.h \
    scenes/defaultscene.h \
    process/controls/controlbool.h \
    process/controls/controlbutton.h \
    process/controls/controlcolor.h \
    process/controls/controldouble.h \
    process/controls/controlimage.h \
    process/controls/controlint.h \
    process/controls/controlstring.h \
    process/controls/icontrol.h

SOURCES += \
    gui/mainwindow.cpp \
    gui/nodeitem.cpp \
    process/node.cpp \
    manager.cpp \
    main.cpp \
    process/opencv/cameranode.cpp \
    process/opencv/debugnode.cpp \
    process/opencv/colornode.cpp \
    gui/linkitem.cpp \
    process/graphics/graphic.cpp \
    process/graphics/scene.cpp \
    process/graphics/tools.cpp \
    process/graphics/elements/color.cpp \
    process/graphics/elements/image.cpp \
    process/graphics/elements/point.cpp \
    process/graphics/threads/loadimagethread.cpp \
    process/graphics/threads/saveimagethread.cpp \
    process/graphics/viewnode.cpp \
    scenes/defaultscene.cpp \
    process/controls/controlbool.cpp \
    process/controls/controlbutton.cpp \
    process/controls/controlcolor.cpp \
    process/controls/controldouble.cpp \
    process/controls/controlimage.cpp \
    process/controls/controlint.cpp \
    process/controls/controlstring.cpp

RESOURCES += \
icons.qrc

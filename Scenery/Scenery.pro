QT += widgets opengl network

TARGET = Scenery
TEMPLATE = app

win32:INCLUDEPATH += c:/opencv/include
win32:LIBS += c:/opencv/lib/*.a

unix:LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so

CONFIG += c++11

HEADERS += \
#    gui/controls/controlstringwidget.h \
#    gui/controls/controlintwidget.h \
#    gui/controls/controldoublewidget.h \
#    gui/controls/controlcolorwidget.h \
#    gui/controls/controlbuttonwidget.h \
#    gui/controls/controlboolwidget.h \
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
    process/graphics/controls/controlbool.h \
    process/graphics/controls/controlbutton.h \
    process/graphics/controls/controlcolor.h \
    process/graphics/controls/controldouble.h \
    process/graphics/controls/controlimage.h \
    process/graphics/controls/controlint.h \
    process/graphics/controls/controlstring.h \
    process/graphics/controls/icontrol.h \
    process/graphics/viewnode.h \
    scenes/defaultscene.h

SOURCES += \
#    gui/controls/controlstringwidget.cpp \
#    gui/controls/controlintwidget.cpp \
#    gui/controls/controldoublewidget.cpp \
#    gui/controls/controlcolorwidget.cpp \
#    gui/controls/controlbuttonwidget.cpp \
#    gui/controls/controlboolwidget.cpp \
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
    process/graphics/controls/controlbool.cpp \
    process/graphics/controls/controlbutton.cpp \
    process/graphics/controls/controlcolor.cpp \
    process/graphics/controls/controldouble.cpp \
    process/graphics/controls/controlimage.cpp \
    process/graphics/controls/controlint.cpp \
    process/graphics/controls/controlstring.cpp \
    process/graphics/viewnode.cpp \
    scenes/defaultscene.cpp

RESOURCES += \
icons.qrc

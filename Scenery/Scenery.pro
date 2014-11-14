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
    gui/linkitem.h

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
    gui/linkitem.cpp

RESOURCES += \
icons.qrc

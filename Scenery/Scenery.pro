QT += gui opengl network

TARGET = Scenery
TEMPLATE = app

win32:INCLUDEPATH += c:/opencv/include
win32:LIBS += c:/opencv/lib/*.a

unix:LIBS += /usr/local/lib/libopencv_*.so

HEADERS += \
    graphics/controls/icontrol.h \
    graphics/controls/controlstring.h \
    graphics/controls/controlint.h \
    graphics/controls/controlimage.h \
    graphics/controls/controldouble.h \
    graphics/controls/controlcolor.h \
    graphics/controls/controlbutton.h \
    graphics/controls/controlbool.h \
    graphics/elements/point.h \
    graphics/elements/image.h \
    graphics/elements/color.h \
    graphics/view.h \
    graphics/tools.h \
    graphics/sceneprocess.h \
    graphics/scene.h \
    graphics/iscene.h \
    graphics/graphic.h \
    graphics/threads/saveimagethread.h \
    graphics/threads/loadimagethread.h \
    gui/controls/controlstringwidget.h \
    gui/controls/controlintwidget.h \
    gui/controls/controldoublewidget.h \
    gui/controls/controlcolorwidget.h \
    gui/controls/controlbuttonwidget.h \
    gui/controls/controlboolwidget.h \
    gui/processwindow.h \
    gui/mainwindow.h \
    process/processtools.h \
    process/processfilters.h \
    process/processdebug.h \
    process/processdata.h \
    process/process.h \
    process/input.h \
    process/clustering.h \
    server/socket.h \
    server/server.h \
    node.h \
    manager.h \
    scenes/Dance/shift.h \
    scenes/Dance/memorize.h \
    scenes/Dance/dancestrings.h \
    scenes/Dance/danceeffects.h \
    scenes/DK/staticimage.h \
    scenes/DK/effect02.h \
    scenes/DK/effect01.h \
    scenes/Skeleton/skeleton.h \
    scenes/Table/fractals.h \
    scenes/VLMT/strings.h \
    scenes/VLMT/inking.h \
    scenes/VLMT/cage.h \
    scenes/VLMT/brush.h \
    scenes/managervlmt.h \
    scenes/managertv.h \
    scenes/managertable.h \
    scenes/managermotion.h \
    scenes/managerdk.h \
    scenes/managerdance.h \
    scenes/manager2cameras.h

SOURCES += \
    graphics/controls/controlstring.cpp \
    graphics/controls/controlint.cpp \
    graphics/controls/controlimage.cpp \
    graphics/controls/controldouble.cpp \
    graphics/controls/controlcolor.cpp \
    graphics/controls/controlbutton.cpp \
    graphics/controls/controlbool.cpp \
    graphics/elements/point.cpp \
    graphics/elements/image.cpp \
    graphics/elements/color.cpp \
    graphics/view.cpp \
    graphics/tools.cpp \
    graphics/sceneprocess.cpp \
    graphics/scene.cpp \
    graphics/graphic.cpp \
    graphics/threads/saveimagethread.cpp \
    graphics/threads/loadimagethread.cpp \
    gui/controls/controlstringwidget.cpp \
    gui/controls/controlintwidget.cpp \
    gui/controls/controldoublewidget.cpp \
    gui/controls/controlcolorwidget.cpp \
    gui/controls/controlbuttonwidget.cpp \
    gui/controls/controlboolwidget.cpp \
    gui/processwindow.cpp \
    gui/mainwindow.cpp \
    process/processtools.cpp \
    process/processfilters.cpp \
    process/processdebug.cpp \
    process/process.cpp \
    process/input.cpp \
    process/clustering.cpp \
    server/socket.cpp \
    server/server.cpp \
    node.cpp \
    manager.cpp \
    main.cpp \
    scenes/Dance/shift.cpp \
    scenes/Dance/memorize.cpp \
    scenes/Dance/dancestrings.cpp \
    scenes/Dance/danceeffects.cpp \
    scenes/DK/staticimage.cpp \
    scenes/DK/effect02.cpp \
    scenes/DK/effect01.cpp \
    scenes/Skeleton/skeleton.cpp \
    scenes/Table/fractals.cpp \
    scenes/VLMT/strings.cpp \
    scenes/VLMT/inking.cpp \
    scenes/VLMT/cage.cpp \
    scenes/VLMT/brush.cpp \
    scenes/managervlmt.cpp \
    scenes/managertv.cpp \
    scenes/managertable.cpp \
    scenes/managermotion.cpp \
    scenes/managerdk.cpp \
    scenes/managerdance.cpp \
    scenes/manager2cameras.cpp

RESOURCES += \
icons.qrc

FORMS += \
    gui/processwindow.ui \
    gui/mainwindow.ui

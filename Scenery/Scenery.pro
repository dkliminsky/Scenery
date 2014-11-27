QT += widgets opengl network

TARGET = Scenery
TEMPLATE = app

win32:INCLUDEPATH += . \
    c:/opencv/opencv-2.4.10_vs12x64/include/

win32:LIBS += c:/opencv/opencv-2.4.10_vs12x64/lib/*.lib

unix:LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so

HEADERS += \
    node.h \
    manager.h \
    graphics/controls/icontrol.h \
    graphics/controls/controlstring.h \
    graphics/controls/controlint.h \
    graphics/controls/controlimage.h \
    graphics/controls/controldouble.h \
    graphics/controls/controlcolor.h \
    graphics/controls/controlbutton.h \
    graphics/controls/controlbool.h \
    graphics/elements/rect.h \
    graphics/elements/point.h \
    graphics/elements/image.h \
    graphics/elements/color.h \
    graphics/threads/saveimagethread.h \
    graphics/threads/loadimagethread.h \
    graphics/view.h \
    graphics/tools.h \
    graphics/sceneprocess.h \
    graphics/scene.h \
    graphics/iscene.h \
    graphics/graphic.h \
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
    scenes/DK/staticimage.h \
    scenes/DK/effect03.h \
    scenes/DK/effect02.h \
    scenes/DK/effect01.h \
    scenes/skeleton/speedtest.h \
    scenes/skeleton/skeleton.h \
    scenes/table/fractals.h \
    scenes/VLMT/strings.h \
    scenes/VLMT/inking.h \
    scenes/VLMT/cage.h \
    scenes/VLMT/brush.h \
    scenes/managervlmt.h \
    scenes/managertable.h \
    scenes/managermotion.h \
    scenes/managerdk.h \
    scenes/manager2cameras.h \
    server/socket.h \
    server/server.h \
    scenes/VLMT/stars.h \
    gui/controls/icontrolwidget.h \
    gui/controls/controlimagewidget.h

SOURCES += \
    node.cpp \
    manager.cpp \
    main.cpp \
    graphics/controls/controlstring.cpp \
    graphics/controls/controlint.cpp \
    graphics/controls/controlimage.cpp \
    graphics/controls/controldouble.cpp \
    graphics/controls/controlcolor.cpp \
    graphics/controls/controlbutton.cpp \
    graphics/controls/controlbool.cpp \
    graphics/elements/rect.cpp \
    graphics/elements/point.cpp \
    graphics/elements/image.cpp \
    graphics/elements/color.cpp \
    graphics/threads/saveimagethread.cpp \
    graphics/threads/loadimagethread.cpp \
    graphics/view.cpp \
    graphics/tools.cpp \
    graphics/sceneprocess.cpp \
    graphics/scene.cpp \
    graphics/graphic.cpp \
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
    scenes/DK/staticimage.cpp \
    scenes/DK/effect03.cpp \
    scenes/DK/effect02.cpp \
    scenes/DK/effect01.cpp \
    scenes/skeleton/speedtest.cpp \
    scenes/skeleton/skeleton.cpp \
    scenes/table/fractals.cpp \
    scenes/VLMT/strings.cpp \
    scenes/VLMT/inking.cpp \
    scenes/VLMT/cage.cpp \
    scenes/VLMT/brush.cpp \
    scenes/managervlmt.cpp \
    scenes/managertable.cpp \
    scenes/managermotion.cpp \
    scenes/managerdk.cpp \
    scenes/manager2cameras.cpp \
    server/socket.cpp \
    server/server.cpp \
    scenes/VLMT/stars.cpp \
    gui/controls/controlimagewidget.cpp

RESOURCES += \
    icons.qrc

FORMS += \
    gui/processwindow.ui \
    gui/mainwindow.ui

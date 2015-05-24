QT += widgets opengl network

TARGET = Scenery
TEMPLATE = app

win32 {
    INCLUDEPATH += . \
        c:/opencv/opencv-2.4.10_vs12x64/include/ \
        "c:/Program Files/Microsoft SDKs/Kinect/v1.8/inc"

    LIBS += c:/opencv/opencv-2.4.10_vs12x64/lib/*.lib \
        "c:/Program Files/Microsoft SDKs/Kinect/v1.8/lib/amd64/Kinect10.lib"

    HEADERS += \
        nodes/kinect/KinectHelper.h \
        nodes/kinect/kinectnode.h \
        nodes/kinect/OpenCVFrameHelper.h

    SOURCES += \
        nodes/kinect/kinectnode.cpp \
        nodes/kinect/OpenCVFrameHelper.cpp \
}

unix:!macx {
    LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so
    DEFINES += NOKINECT

    HEADERS += \
        nodes/kinect/kinectfakenode.h

    SOURCES += \
        nodes/kinect/kinectfakenode.cpp
}

macx {
    INCLUDEPATH += /usr/local/include/
    LIBS += /usr/local/lib/libopencv_*.a

    DEFINES += NOKINECT

    HEADERS += \
        nodes/kinect/kinectfakenode.h

    SOURCES += \
        nodes/kinect/kinectfakenode.cpp
}

CONFIG += c++11

HEADERS += \
    gui/mainwindow.h \
    gui/nodeitem.h \
    nodes/node.h \
    nodes/opencv/cameranode.h \
    nodes/opencv/debugnode.h \
    debug.h \
    nodes/opencv/colornode.h \
    gui/linkitem.h \
    nodes/graphics/graphic.h \
    nodes/graphics/scene.h \
    nodes/graphics/tools.h \
    nodes/graphics/elements/color.h \
    nodes/graphics/elements/image.h \
    nodes/graphics/threads/loadimagethread.h \
    nodes/graphics/threads/saveimagethread.h \
    controls/controlbool.h \
    controls/controlbutton.h \
    controls/controlcolor.h \
    controls/controldouble.h \
    controls/controlimage.h \
    controls/controlint.h \
    controls/controlstring.h \
    nodes/nodes.h \
    controls/controls.h \
    nodes/opencv/erodenode.h \
    gui/controls/controlboolwidget.h \
    gui/controls/controlbuttonwidget.h \
    gui/controls/controlcolorwidget.h \
    gui/controls/controldoublewidget.h \
    gui/controls/controlintwidget.h \
    gui/controls/controlstringwidget.h \
    gui/controls/controlwidgets.h \
    nodes/opencv/dilatenode.h \
    nodes/graphics/scenesnode.h \
    nodes/graphics/view.h \
    nodes/graphics/elements/elements.h \
    nodes/graphics/elements/position.h \
    nodes/kinect/OpenCVHelper.h \
    nodes/kinect/human.h \
    nodes/graphics/elements/particle.h \
    nodes/controls/controlgroup.h \
    gui/controls/controlgroupwidget.h \
    nodes/opencv/rectnode.h \
    gui/controls/controlimagewidget.h \
    nodes/kinect/gesturenode.h \
    nodes/project.h \
    controls/control.h \
    controls/controlprovider.h \
    controls/controlgroup.h

SOURCES += \
    gui/mainwindow.cpp \
    gui/nodeitem.cpp \
    nodes/node.cpp \
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
    nodes/graphics/threads/loadimagethread.cpp \
    nodes/graphics/threads/saveimagethread.cpp \
    controls/controlbool.cpp \
    controls/controlbutton.cpp \
    controls/controlcolor.cpp \
    controls/controldouble.cpp \
    controls/controlimage.cpp \
    controls/controlint.cpp \
    controls/controlstring.cpp \
    nodes/opencv/erodenode.cpp \
    gui/controls/controlboolwidget.cpp \
    gui/controls/controlbuttonwidget.cpp \
    gui/controls/controlcolorwidget.cpp \
    gui/controls/controldoublewidget.cpp \
    gui/controls/controlintwidget.cpp \
    gui/controls/controlstringwidget.cpp \
    gui/controls/controlwidgets.cpp \
    nodes/opencv/dilatenode.cpp \
    nodes/graphics/scenesnode.cpp \
    nodes/graphics/view.cpp \
    scenes/dance.cpp \
    scenes/example.cpp \
    nodes/kinect/OpenCVHelper.cpp \
    nodes/graphics/elements/particle.cpp \
    controls/controlgroup.cpp \
    gui/controls/controlgroupwidget.cpp \
    nodes/opencv/rectnode.cpp \
    gui/controls/controlimagewidget.cpp \
    nodes/kinect/gesturenode.cpp \
    nodes/project.cpp \
    controls/controlprovider.cpp \
    controls/control.cpp \
    scenes/shadow.cpp

RESOURCES += \
    resources.qrc



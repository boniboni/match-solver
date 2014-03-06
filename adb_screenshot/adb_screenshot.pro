#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T08:10:49
#
#-------------------------------------------------

QT += core
QT += network
QT += gui
QT += widgets


TARGET = adb_screenshot
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app


QMAKE_LFLAGS_WINDOWS += -Wl,--stack,32000000


SOURCES += main.cpp \
    remote.cpp \
    fb2png.cpp \
    creatematrix.cpp \
    sortit.cpp

HEADERS += \
    fb.h \
    remote.h \
    fb2png.h \
    creatematrix.h \
    sortit.h

INCLUDEPATH += C:\\Qt\\opencv_bin\\install\\include \

                   C:\\Qt\\opencv_bin\\install\\include\\opencv \

                   C:\\Qt\\opencv_bin\\install\\include\\opencv2 \


LIBS += -LC:\\Qt\\opencv_bin\\install\x64\\mingw\\bin \
    libopencv_core248d \
    libopencv_highgui248d \
    libopencv_imgproc248d \
    libopencv_features2d248d \
    libopencv_calib3d248d \

QT       += quick opengl


TARGET = cocos2d-qt
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11
CONFIG += precompile_header

DEFINES += CC_TARGET_OS_MAC=1

PRECOMPILED_HEADER  += src/precompiled.h

include(cocos2dx.pri)


SOURCES += \
    src/CCApplication.cpp \
    src/CCCommon.cpp \
    src/CCDevice.cpp \
    src/CCFileUtilsQt.cpp \
    src/CCGLView.cpp \
    src/fborender/FboRenderer.cpp \
    src/objectrender/ObjectRenderer.cpp \
    src/threadrender/ThreadRenderer.cpp

HEADERS += src/precompiled.h \
    src/CCApplication.h \
    src/CCFileUtilsQt.h \
    src/CCGLView.h \
    src/fborender/FboRenderer.h \
    src/objectrender/ObjectRenderer.h \
    src/threadrender/ThreadRenderer.h


#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

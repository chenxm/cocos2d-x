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
    src/CCCommon.cpp \
    src/CCDevice.cpp \
    src/fborender/FboRenderer.cpp \
    src/objectrender/ObjectRenderer.cpp \
    src/threadrender/ThreadRenderer.cpp \
    src/Application.cpp \
    src/GLViewImpl.cpp \
    src/FileUtilsImpl.cpp

HEADERS += src/precompiled.h \
    src/fborender/FboRenderer.h \
    src/objectrender/ObjectRenderer.h \
    src/threadrender/ThreadRenderer.h \
    src/QtCoordinate.h \
    src/Application.h \
    src/GLViewImpl.h \
    src/FileUtilsImpl.h


#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

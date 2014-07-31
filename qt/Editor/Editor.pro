TEMPLATE = app
DESTDIR = ..

QT += qml quick
# To make threaded gl check...
#QT += core-private gui-private

CONFIG += c++11
CONFIG += precompile_header

DEFINES += CC_TARGET_OS_MAC=1

DEPLOY_RES  = $$PWD/media/deploy
SCRIPTS_RES = $$PWD/../../cocos/scripting/lua-bindings/script

macx {
    contains(CONFIG, app_bundle) {
        APP_BUNDLE = $${DESTDIR}/$${TARGET}.app
        message("-------------")
        message($${APP_BUNDLE})
        QMAKE_POST_LINK += cp -R $$DEPLOY_RES/* $$APP_BUNDLE/Contents/Resources &
    }
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


PRECOMPILED_HEADER  += precompiled.h


include(../cocos2d-qt/cocos2dx.pri)
INCLUDEPATH += $$PWD/../cocos2d-qt/src
LIBS += -L$$PWD/../lib -lcocos2d-qt

# Default rules for deployment.
include(deployment.pri)


RESOURCES += qml.qrc

OTHER_FILES += \
    main.qml

HEADERS += precompiled.h\
    src/AppDelegate.h \
    src/HelloWorldScene.h

SOURCES += main.cpp \
    src/AppDelegate.cpp \
    src/HelloWorldScene.cpp

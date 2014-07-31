TEMPLATE = app
DESTDIR = ..


QT += qml quick


CONFIG += c++11
CONFIG += precompile_header

DEFINES += CC_TARGET_OS_MAC=1
DEFINES += COCOS2D_DEBUG=1

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

PRECOMPILED_HEADER  += precompiled.h

include(../cocos2d-qt/cocos2dx.pri)
INCLUDEPATH += $$PWD/../cocos2d-qt/src
LIBS += -L$$PWD/../lib -lcocos2d-qt

RESOURCES += openglunderqml.qrc

HEADERS += precompiled.h \
    src/AppDelegate.h \
    src/HelloWorldScene.h \


SOURCES += main.cpp \
    src/AppDelegate.cpp \
    src/HelloWorldScene.cpp

OTHER_FILES += \
    main.qml

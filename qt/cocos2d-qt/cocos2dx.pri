

macx {
    # system libraries.
    LIBS += -lz
    LIBS += -lcurl
    LIBS += -lsqlite3

    QMAKE_CXXFLAGS += -F/Library/Frameworks
    QMAKE_LFLAGS += -F/Library/Frameworks

    LIBS    += -framework Cocoa
    LIBS    += -framework Foundation
    LIBS    += -framework OpenAL
    LIBS    += -framework Ogg
    LIBS    += -framework Vorbis

    # prebuilt libraries
    INCLUDEPATH += $$PWD/../../external/png/include/mac
    LIBS += $$PWD/../../external/png/prebuilt/mac/libpng.a

    INCLUDEPATH += $$PWD/../../external/tiff/include/mac
    LIBS += $$PWD/../../external/tiff/prebuilt/mac/libtiff.a

    INCLUDEPATH += $$PWD/../../external/jpeg/include/mac
    LIBS += $$PWD/../../external/jpeg/prebuilt/mac/libjpeg.a

    INCLUDEPATH += $$PWD/../../external/freetype2/include/mac
    LIBS += $$PWD/../../external/freetype2/prebuilt/mac/libfreetype.a

    INCLUDEPATH += $$PWD/../../external/websockets/include/mac
    LIBS += $$PWD/../../external/websockets/prebuilt/mac/libwebsockets.a

    INCLUDEPATH += $$PWD/../../external/webp/include/mac
    LIBS += $$PWD/../../external/webp/prebuilt/mac/libwebp.a

    INCLUDEPATH += $$PWD/../../external/lua/luajit/include
    LIBS += -L$$PWD/../../external/lua/luajit/prebuilt/mac -lluajit

    INCLUDEPATH += /usr/include
    LIBS += /usr/lib/libGLEW.a

    LIBS += $$PWD/../lib/mac/libcocos2d.a

    INCLUDEPATH += $$PWD/../../cocos/platform/mac
}



INCLUDEPATH += \
$$PWD/src \
$$PWD/../../cocos \
$$PWD/../../cocos/platform


SOURCES += \

HEADERS += \

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    army.cpp \
    building.cpp \
    game.cpp \
    kingdom.cpp \
    main.cpp \
    map.cpp \
    resources.cpp

HEADERS += \
    army.h \
    building.h \
    game.h \
    kingdom.h \
    map.h \
    resources.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Add SFML include and lib paths
INCLUDEPATH += $$PWD/SFML-2.6.1/include
LIBS += -L$$PWD/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system


# Copy SFML DLLs to build directory
win32 {
    CONFIG(debug, debug|release) {
        DLL_DIR = $$PWD/SFML-2.6.1/bin
        DEST_DIR = $$OUT_PWD/debug
    } else {
        DLL_DIR = $$PWD/SFML-2.6.1/bin
        DEST_DIR = $$OUT_PWD/release
    }

    COPIES += copy_dlls
    copy_dlls.files = $$files($$DLL_DIR/*.dll)
    copy_dlls.path = $$DEST_DIR
}

# Kopiowanie folderu sprites
win32 {
    SPRITES_DIR = $$PWD/sprites
    DEST_SPRITES_DIR = $$OUT_PWD/sprites

    COPIES += copy_sprites
    copy_sprites.files = $$files($$SPRITES_DIR/*)
    copy_sprites.path = $$DEST_SPRITES_DIR
}

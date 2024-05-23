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
    mainwindow.cpp \
    map.cpp \
    resources.cpp

HEADERS += \
    army.h \
    building.h \
    game.h \
    kingdom.h \
    mainwindow.h \
    map.h \
    resources.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

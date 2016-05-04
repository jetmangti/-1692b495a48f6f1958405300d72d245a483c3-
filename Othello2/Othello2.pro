QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Othello2
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += qt gui

SOURCES += main.cpp \
    mainwindow.cpp \
    cell.cpp \
    ai1.cpp \
    ai2.cpp \
    aiselector.cpp \
    gamecontroller.cpp \
    cellfinder.cpp \
    gamesetting.cpp \
    cligame.cpp \
    guigame.cpp \
    game.cpp

HEADERS += \
    mainwindow.h \
    cell.h \
    ai1.h \
    ai2.h \
    aiselector.h \
    gamecontroller.h \
    cellfinder.h \
    gamesetting.h \
    enumm.h \
    includes.h \
    cligame.h \
    guigame.h \
    game.h \
    runnable.h

FORMS    += mainwindow.ui \
    mainwindow.ui

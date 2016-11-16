#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T18:38:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EduApp
TEMPLATE = app

SOURCES += \
    src/Main.cpp

HEADERS +=

CONFIG(debug, debug|release): LIBS += -L$$PWD/ext/SFML/debug/lib
CONFIG(release, debug|release): LIBS += -L$$PWD/ext/SFML/release/lib

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/ext/SFML/include
DEPENDPATH += $$PWD/ext/SFML/include

CONFIG(debug, debug|release): LIBS += -L$$PWD/ext/Box2D/debug -lBox2D
CONFIG(release, debug|release): LIBS += -L$$PWD/ext/Box2D/release -lBox2D

INCLUDEPATH += $$PWD/ext/Box2D
DEPENDPATH += $$PWD/ext/Box2D

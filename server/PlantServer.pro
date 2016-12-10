#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T10:25:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SFMLQtServer
TEMPLATE = app

FORMS += \
    src/MainWindow.ui

HEADERS += \
    src/MainWindow.h

SOURCES += \
    src/Main.cpp \
    src/MainWindow.cpp


EXTDIR = $$PWD/../ext

LIBS += -L$${EXTDIR}/SFML-2.4.1/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $${EXTDIR}/SFML-2.4.1/include
DEPENDPATH += $${EXTDIR}/SFML-2.4.1/include

CONFIG(release, debug|release): LIBS += -L$${EXTDIR}/MySQL/ -llibmysql
CONFIG(debug, debug|release): LIBS += -L$${EXTDIR}/MySQL/ -llibmysql



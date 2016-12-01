#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T10:25:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SFMLQtServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

!macx{
CONFIG(debug, debug|release): LIBS += -L../../ext/SFML/debug/lib
CONFIG(release, debug|release): LIBS += -L../../ext/SFML/release/lib

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += ../../ext/SFML/include
DEPENDPATH += ../../ext/SFML/include
}

macx{
    LIBS += -L"/usr/local/lib" -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

    INCLUDEPATH += "/usr/local/include"
    DEPENDPATH += "/usr/local/include"

}

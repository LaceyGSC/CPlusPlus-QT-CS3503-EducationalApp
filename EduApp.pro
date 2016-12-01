#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T18:38:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EduApp
TEMPLATE = app

SOURCES += \
    src/Main.cpp \
    src/QSFMLWidget.cpp \
    src/World.cpp \
    src/ResourceManager.inl \
    src/Application.cpp \
    src/State.cpp \
    src/StateStack.cpp \
    src/GameState.cpp \
    src/FractalExspressionEvaluator.cpp \
    src/ServerConnection.cpp
#    src/Character.cpp \
    src/ServerConnection.cpp

HEADERS += \
    src/QSFMLWidget.h \
    src/World.h \
    src/ResourceManager.h \
    src/ResourceIdentifiers.h \
    src/Application.h \
    src/State.h \
    src/StateStack.h \
    src/StateIdentifiers.h \
    src/GameState.h \
    src/FractalExspressionEvaluator.h \
    src/ServerConnection.h
#    src/Character.h \
    src/ServerConnection.h

FORMS += \
    src/Application.ui \
    src/GameState.ui

RESOURCES += \
    src/Textures.qrc

!macx{
CONFIG(debug, debug|release): LIBS += -L$$PWD/ext/SFML/debug/lib
CONFIG(release, debug|release): LIBS += -L$$PWD/ext/SFML/release/lib

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/ext/SFML/include
DEPENDPATH += $$PWD/ext/SFML/include
}

macx{
    #LIBS += -L$$PWD/ext/SFML-2.4.1-osx-clang/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

    #INCLUDEPATH += $$PWD/ext/SFML-2.4.1-osx-clang/include
    #DEPENDPATH += $$PWD/ext/SFML-2.4.1-osx-clang/include
QMAKE_MAC_SDK = macosx10.12

LIBS += -L"/usr/local/lib" -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"

    #QMAKE_+= $$PWD/ext/SFML-2.4.1-osx-clang/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window
}


!mac{
CONFIG(debug, debug|release): LIBS += -L$$PWD/ext/Box2D/debug -lBox2D
CONFIG(release, debug|release): LIBS += -L$$PWD/ext/Box2D/release -lBox2D

INCLUDEPATH += $$PWD/ext/Box2D
DEPENDPATH += $$PWD/ext/Box2D

}

macx{
LIBS += -L$$PWD/ext/Box2D/debug/ -lBox2D

INCLUDEPATH += $$PWD/ext/Box2D
DEPENDPATH += $$PWD/ext/Box2D

PRE_TARGETDEPS += $$PWD/ext/Box2D/debug/libBox2D.a
}

mac{
QMAKE_POST_LINK="install_name_tool -add_rpath $$PWD/ext/SFML-2.4.1-osx-clang/lib/ $$OUT_PWD/EduApp.app/Contents/MacOS/EduApp && install_name_tool -add_rpath $$PWD/ext/SFML-2.4.1-osx-clang/extlibs/Frameworks/vorbisenc.framework/Versions/A/vorbisenc $$OUT_PWD/EduApp.app/Contents/MacOS/EduApp"
}


!mac{

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ext/MySQL/ -llibmysql

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ext/MySQL/ -llibmysql

}


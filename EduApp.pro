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
    src/LoginState.cpp \
    src/FractalExspressionEvaluator.cpp \
    src/ServerConnection.cpp \
    src/Plantodex.cpp \
    src/AdminState.cpp \
    src/Character.cpp  \
    src/Level.cpp \
    src/Quest.cpp \
    src/Commands.cpp \
    src/SubQuest.cpp \
    src/SQCollectProperties.cpp \
    src/SQCollectSpecific.cpp \
    src/SQCollectType.cpp \
    src/LevelManager.cpp \
    src/Reward.cpp \
    src/QuickPlantAnalyzer.cpp \
    src/WorldCanvas.cpp \
    src/TileManager.cpp \
    src/SettingsUI.cpp \
    src/TitleState.cpp \
    src/SplashScreen.cpp \
    src/ManualDialog.cpp \
    src/Player.cpp

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
    src/FractalExpressionEvaluator.h \
    src/ServerConnection.h \
    src/Plantodex.h \
    src/ServerConnection.h \
    src/LoginState.h \
    src/AdminState.h \
    src/Character.h  \
    src/Level.h \
    src/Quest.h \
    src/Commands.h \
    src/SubQuest.h \
    src/SQCollectProperties.h \
    src/SQCollectSpecific.h \
    src/SQCollectType.h \
    src/LevelManager.h \
    src/Reward.h \
    src/QuickPlantAnalyzer.h \
    src/Identifiers.h \
    src/WorldCanvas.h \
    src/TileManager.h \
    src/SettingsUI.h \
    src/TitleState.h \
    src/SplashScreen.h \
    src/ManualDialog.h \
    src/Player.h

FORMS += \
    src/Application.ui \
    src/GameState.ui \
    src/LoginState.ui \
    src/Plantodex.ui \
    src/Level.ui \
    src/Quest.ui \
    src/Reward.ui \
    src/QuickPlantAnalyzer.ui \
    src/SettingsUI.ui \
    src/ManualDialog.ui \
    src/TitleState.ui \
    src/Player.ui
    src/TitleState.ui
    src/AdminState.ui

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

macx{
QMAKE_POST_LINK="install_name_tool -add_rpath $$PWD/ext/SFML-2.4.1-osx-clang/lib/ $$OUT_PWD/EduApp.app/Contents/MacOS/EduApp && install_name_tool -add_rpath $$PWD/ext/SFML-2.4.1-osx-clang/extlibs/Frameworks/vorbisenc.framework/Versions/A/vorbisenc $$OUT_PWD/EduApp.app/Contents/MacOS/EduApp"
}


!mac{

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ext/MySQL/ -llibmysql

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ext/MySQL/ -llibmysql

}


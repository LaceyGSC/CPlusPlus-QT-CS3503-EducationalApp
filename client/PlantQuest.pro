#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T13:11:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlantQuest
TEMPLATE = app


SOURCES += \
    src/AdminState.cpp \
    src/Application.cpp \
    src/Commands.cpp \
    src/FractalExpressionEvaluator.cpp \
    src/GameState.cpp \
    src/Level.cpp \
    src/LevelManager.cpp \
    src/LoginState.cpp \
    src/Main.cpp \
    src/ManualDialog.cpp \
    src/Plantodex.cpp \
    src/Player.cpp \
    src/QSFMLWidget.cpp \
    src/Quest.cpp \
    src/QuickPlantAnalyzer.cpp \
    src/ResourceManager.inl \
    src/Reward.cpp \
    src/Satchel.cpp \
    src/ServerConnection.cpp \
    src/SettingsUI.cpp \
    src/SplashScreen.cpp \
    src/SQCollectProperties.cpp \
    src/SQCollectSpecific.cpp \
    src/SQCollectType.cpp \
    src/State.cpp \
    src/StateStack.cpp \
    src/SubQuest.cpp \
    src/TileManager.cpp \
    src/TitleState.cpp \
    src/UserData.cpp \
    src/WorldCanvas.cpp \
    src/MusicPlayer.cpp

HEADERS  += \
    src/AdminState.h \
    src/Application.h \
    src/Commands.h \
    src/FractalExpressionEvaluator.h \
    src/GameState.h \
    src/Identifiers.h \
    src/Level.h \
    src/LevelManager.h \
    src/LoginState.h \
    src/ManualDialog.h \
    src/Plantodex.h \
    src/Player.h \
    src/QSFMLWidget.h \
    src/Quest.h \
    src/QuickPlantAnalyzer.h \
    src/ResourceManager.h \
    src/Reward.h \
    src/Satchel.h \
    src/ServerConnection.h \
    src/SettingsUI.h \
    src/SplashScreen.h \
    src/SQCollectProperties.h \
    src/SQCollectSpecific.h \
    src/SQCollectType.h \
    src/State.h \
    src/StateStack.h \
    src/SubQuest.h \
    src/TileManager.h \
    src/TitleState.h \
    src/UserData.h \
    src/WorldCanvas.h \
    src/MusicPlayer.h

FORMS    += \
    src/AdminState.ui \
    src/Application.ui \
    src/GameState.ui \
    src/Level.ui \
    src/LoginState.ui \
    src/ManualDialog.ui \
    src/Plantodex.ui \
    src/Player.ui \
    src/Quest.ui \
    src/QuickPlantAnalyzer.ui \
    src/Reward.ui \
    src/SettingsUI.ui \
    src/TitleState.ui

RESOURCES += \
    Media.qrc

EXTDIR = $$PWD/../ext

!macx{

LIBS += -L$${EXTDIR}/SFML-2.4.1/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $${EXTDIR}/SFML-2.4.1/include
DEPENDPATH += $${EXTDIR}/SFML-2.4.1/include

CONFIG(release, debug|release): LIBS += -L$${EXTDIR}/Box2D/release -lBox2D
CONFIG(debug, debug|release): LIBS += -L$${EXTDIR}/Box2D/debug -lBox2D

INCLUDEPATH += $${EXTDIR}/Box2D
DEPENDPATH += $${EXTDIR}/Box2D
}

macx{

QMAKE_MAC_SDK = macosx10.12

LIBS += -L"/usr/local/lib" -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"

LIBS += -L$${EXTDIR}/Box2D/debug/ -lBox2D

INCLUDEPATH += $${EXTDIR}/Box2D
DEPENDPATH += $${EXTDIR}/Box2D

PRE_TARGETDEPS += $${EXTDIR}/Box2D/debug/libBox2D.a

QMAKE_POST_LINK="install_name_tool -add_rpath $${EXTDIR}/SFML-2.4.1-osx-clang/lib/ $$OUT_PWD/EduApp.app/Contents/MacOS/EduApp && install_name_tool -add_rpath $${EXTDIR}/SFML-2.4.1-osx-clang/extlibs/Frameworks/vorbisenc.framework/Versions/A/vorbisenc $$OUT_PWD/EduApp.app/Contents/MacOS/EduApp"
}

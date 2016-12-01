/********************************************************************************
** Form generated from reading UI file 'GameState.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESTATE_H
#define UI_GAMESTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameState
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gameContainer;
    QGroupBox *worldBox;
    QGridLayout *gridLayout_3;
    QGridLayout *worldContainer;
    QGroupBox *charStatsBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *plantodexButton;

    void setupUi(QWidget *GameState)
    {
        if (GameState->objectName().isEmpty())
            GameState->setObjectName(QStringLiteral("GameState"));
        GameState->setEnabled(true);
        GameState->resize(251, 96);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GameState->sizePolicy().hasHeightForWidth());
        GameState->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(GameState);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gameContainer = new QGridLayout();
        gameContainer->setSpacing(0);
        gameContainer->setObjectName(QStringLiteral("gameContainer"));
        worldBox = new QGroupBox(GameState);
        worldBox->setObjectName(QStringLiteral("worldBox"));
        worldBox->setLayoutDirection(Qt::LeftToRight);
        worldBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout_3 = new QGridLayout(worldBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        worldContainer = new QGridLayout();
        worldContainer->setObjectName(QStringLiteral("worldContainer"));

        gridLayout_3->addLayout(worldContainer, 0, 0, 1, 1);


        gameContainer->addWidget(worldBox, 1, 0, 1, 1);

        charStatsBox = new QGroupBox(GameState);
        charStatsBox->setObjectName(QStringLiteral("charStatsBox"));
        charStatsBox->setEnabled(true);
        gridLayout_2 = new QGridLayout(charStatsBox);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(charStatsBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton, 0, 1, 1, 1);

        plantodexButton = new QPushButton(charStatsBox);
        plantodexButton->setObjectName(QStringLiteral("plantodexButton"));

        gridLayout_2->addWidget(plantodexButton, 1, 1, 1, 1);


        gameContainer->addWidget(charStatsBox, 1, 1, 1, 1);


        gridLayout->addLayout(gameContainer, 0, 0, 1, 1);


        retranslateUi(GameState);

        QMetaObject::connectSlotsByName(GameState);
    } // setupUi

    void retranslateUi(QWidget *GameState)
    {
        GameState->setWindowTitle(QApplication::translate("GameState", "Form", 0));
        worldBox->setTitle(QApplication::translate("GameState", "World Display", 0));
        charStatsBox->setTitle(QApplication::translate("GameState", "Character Statistics", 0));
        pushButton->setText(QApplication::translate("GameState", "Test", 0));
        plantodexButton->setText(QApplication::translate("GameState", "Plantodex", 0));
    } // retranslateUi

};

namespace Ui {
    class GameState: public Ui_GameState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESTATE_H

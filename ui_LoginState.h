/********************************************************************************
** Form generated from reading UI file 'LoginState.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSTATE_H
#define UI_LOGINSTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginState
{
public:
    QLabel *usernameLabel;
    QLineEdit *usernameLine;
    QLabel *passwordLabel;
    QLineEdit *passwordLine;
    QPushButton *loginButton;
    QPushButton *createButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *LoginState)
    {
        if (LoginState->objectName().isEmpty())
            LoginState->setObjectName(QStringLiteral("LoginState"));
        LoginState->resize(400, 300);
        usernameLabel = new QLabel(LoginState);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(70, 60, 81, 16));
        usernameLine = new QLineEdit(LoginState);
        usernameLine->setObjectName(QStringLiteral("usernameLine"));
        usernameLine->setGeometry(QRect(160, 60, 201, 24));
        passwordLabel = new QLabel(LoginState);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(70, 100, 81, 16));
        passwordLine = new QLineEdit(LoginState);
        passwordLine->setObjectName(QStringLiteral("passwordLine"));
        passwordLine->setGeometry(QRect(160, 100, 201, 24));
        passwordLine->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(LoginState);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(60, 180, 80, 25));
        createButton = new QPushButton(LoginState);
        createButton->setObjectName(QStringLiteral("createButton"));
        createButton->setGeometry(QRect(160, 180, 80, 25));
        cancelButton = new QPushButton(LoginState);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(260, 180, 80, 25));

        retranslateUi(LoginState);

        QMetaObject::connectSlotsByName(LoginState);
    } // setupUi

    void retranslateUi(QWidget *LoginState)
    {
        LoginState->setWindowTitle(QApplication::translate("LoginState", "Form", 0));
        usernameLabel->setText(QApplication::translate("LoginState", "Username:", 0));
        passwordLabel->setText(QApplication::translate("LoginState", "Password:", 0));
        loginButton->setText(QApplication::translate("LoginState", "Login", 0));
        createButton->setText(QApplication::translate("LoginState", "Create", 0));
        cancelButton->setText(QApplication::translate("LoginState", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginState: public Ui_LoginState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSTATE_H

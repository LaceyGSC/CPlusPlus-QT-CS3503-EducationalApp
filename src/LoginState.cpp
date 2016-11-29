#include "LoginState.h"
#include "ui_LoginState.h"

LoginState::LoginState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginState)
{
    ui->setupUi(this);
}

LoginState::~LoginState()
{
    delete ui;
}

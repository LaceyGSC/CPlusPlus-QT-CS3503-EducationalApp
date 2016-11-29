#include "loginstate.h"
#include "ui_loginstate.h"

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

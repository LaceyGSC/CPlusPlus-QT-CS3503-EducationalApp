


#include "LoginState.h"
#include "ui_LoginState.h"

LoginState::LoginState(StateStack &stack, Context &context, QWidget *parent) :
    State(stack, context, parent)
    , ui(new Ui::LoginState)
{
    ui->setupUi(this);

    this->show();

    connect(ui->loginButton, SIGNAL(pressed()), this, SLOT(loginSlot()));
}

LoginState::~LoginState()
{
    delete ui;
}

bool LoginState::update(const sf::Time &deltaTime)
{
    return true;
}

void LoginState::createSlot()
{

}

void LoginState::loginSlot()
{
    requestStackPop();
    requestStackPush(States::ID::GameState);
}

void LoginState::cancelSlot()
{

}



#include "LoginState.h"
#include "ui_LoginState.h"

LoginState::LoginState(StateStack &stack, Context &context, QWidget *parent) :
    State(stack, context, parent)
    , ui(new Ui::LoginState)
{
    ui->setupUi(this);

    this->show();

    //Clears notification message on start
    ui->notifyLabel->setText("");


    status = getContext().connection.setupConnection();

    if(status == sf::Socket::NotReady || status == sf::Socket::Error || status == sf::Socket::Disconnected)
    {
        ui->notifyLabel->setText("Server Connection Failed");
        status = getContext().connection.setupConnection();
    }

    connect(ui->loginButton, SIGNAL(pressed()), this, SLOT(loginSlot()));
    connect(ui->createButton, SIGNAL(pressed()), this, SLOT(createSlot()));
    connect(ui->cancelButton, SIGNAL(pressed()), this, SLOT(cancelSlot()));

    getContext().music.play(Music::ID::Login);
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
    status = getContext().connection.setupConnection();

    if(status == sf::Socket::NotReady || status == sf::Socket::Error || status == sf::Socket::Disconnected)
    {
        ui->notifyLabel->setText("Server Connection Failed");
        status = getContext().connection.setupConnection();
    }
    else
    {
        //Gets data from the UI, test for empty values
        QString name = ui->usernameLine->text();
        QString pass = ui->passwordLine->text();


        if(name == "" || pass == "")
        {
            ui->notifyLabel->setText("Fields cannot be empty");
        }
        else
        {
            ui->notifyLabel->setText("");

            std::string sendQuery = "create\n" + name.toStdString() + "\n" + pass.toStdString();

            getContext().connection.sendPacket(sendQuery);

            //Gets result from packet, 1 is success
            // empty string indicates issue with server
            QString resultNum = getContext().connection.getPacket();

            while(resultNum == "")
            {
                resultNum = getContext().connection.getPacket();
            }

            if(resultNum == "0")
            {
                ui->notifyLabel->setText("Failed to create user, Username is already taken");
            }
            else if (resultNum == "1")
            {
                //Creation was successful, starts login process for new user
                loginSlot();
            }
            else if (resultNum == "")
            {
                ui->notifyLabel->setText("Server Connection NotReady");
            }
        }

    }
}

void LoginState::loginSlot()
{
    status = getContext().connection.setupConnection();

    if(status == sf::Socket::NotReady || status == sf::Socket::Error || status == sf::Socket::Disconnected)
    {
        ui->notifyLabel->setText("Server Connection Failed");
        status = getContext().connection.setupConnection();
    }
    else
    {

        QString name = ui->usernameLine->text();
        QString pass = ui->passwordLine->text();

        if(name == "" || pass == "")
        {
            ui->notifyLabel->setText("Fields cannot be empty");
        }
        else
        {
            std::string sendQuery = "login\n" + name.toStdString() + "\n" + pass.toStdString();

            getContext().connection.sendPacket(sendQuery);

            //Gets result from packet, 1 is success
            // empty string indicates issue with server
            QString resultNum = getContext().connection.getPacket();

            while(resultNum == "")
            {
                resultNum = getContext().connection.getPacket();
            }

                if(resultNum == "0")
                {
                    ui->notifyLabel->setText("Login failed, please verify information or contact administrator");
                }
                else if ( resultNum == "1")
                {
                    //Successful login to non admin account

                    //Moves onto the World screen
                    requestStackPop();
                    requestStackPush(States::ID::GameState);
                }
                else if (resultNum == "2")
                {
                    //Successful login to Admin account

                    requestStackPop();
                    requestStackPush(States::ID::AdminState);
                }
       }
    }
}

void LoginState::cancelSlot()
{
    //Actual work for cancel
    exit(0);

}


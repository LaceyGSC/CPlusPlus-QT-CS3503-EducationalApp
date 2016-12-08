#include "AdminState.h"
#include "ui_AdminState.h"
#include "Character.h"
#include <QTableWidget>

AdminState::AdminState(StateStack &stack, Context &context, QWidget *parent) :
    State(stack, context, parent),
    ui(new Ui::AdminState)
{
    ui->setupUi(this);

    connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(deleteSlot()));
    connect(ui->viewButton, SIGNAL(pressed()), this, SLOT(viewSlot()));
    connect(ui->logOutButton, SIGNAL(pressed()), this, SLOT(logSlot()));
    connect(ui->studentTable, SIGNAL(cellClicked(int,int)),this, SLOT(selectedSlot(int, int)));
}

AdminState::~AdminState()
{
    delete ui;
}

bool AdminState::update(const sf::Time &deltaTime)
{
    return true;
}

void AdminState::createArray()
{
     //Gets mass packet of user, divides by newline
     QString allUsers = connection.getPacket();
     QStringList queryList = allUsers.split(QRegExp("\\n+"), QString::SkipEmptyParts);

     QString userID;
     QString username;
     QString password;
     int currentLevel;
     int currentQuest;
     int currentProgress;

     //Iterates through divided list of variables, stores in array of characters
     for(int i = 0; i < queryList.size(); i++)
     {
         userID = queryList.at(i);
         i++;
         username = queryList.at(i);
         i++;
         password = queryList.at(i);
         i++;
         currentLevel = queryList.at(i).toInt();
         i++;
         currentQuest = queryList.at(i).toInt();
         i++;
         currentProgress = queryList.at(i).toInt();

         characterVect.push_back(Character(userID,username,password,currentLevel,currentQuest,currentProgress));
     }

     //Populates the table with the list of characters
     createListView();

}

void AdminState::createListView()
{

    QTableWidgetItem *newItem;

    for(int i = 0; i < characterVect.size(); i++)
    {
        this->ui->studentTable->insertRow(i);

        //Creates clickable item, first col, userid
        newItem = new QTableWidgetItem;
        newItem->setText(characterVect.at(i).userID);;
        this->ui->studentTable->setItem(i,0,newItem);

        //Creates clickable item, second col, name
        newItem = new QTableWidgetItem;
        newItem->setText(characterVect.at(i).username);
        this->ui->studentTable->setItem(i,1,newItem);
    }

}

void AdminState::deleteSlot()
{
    //Gets selected index number, then deletes from the database and the listview
    if(masterNum != 0)
    {
        std::string userID = characterVect.at(masterNum).userID.toStdString();
        std::string sendQuery = "delete " + userID;
        getContext().connection.sendPacket(sendQuery);

        this->ui->idLine->setText("");
        this->ui->usernameLine->setText("");
        this->ui->passwordLine->setText("");
        this->ui->cLevelLine->setText("");
        this->ui->cQuestLine->setText("");
        this->ui->cProgressLine->setText("");

        this->ui->studentTable->removeRow(masterNum);
        characterVect.erase(characterVect.begin() + masterNum);
    }
}

void AdminState::viewSlot()
{
    //Sends request to server to create stats page
    std::string sendQuery = "webpage";
    getContext().connection.sendPacket(sendQuery);
}

void AdminState::logSlot()
{
    //Currently sets up connection for testing, triggers create array to make local copy of data
    //Will be moved into main method when connection issue resolved
    getContext().connection.setupConnection();
    createArray();

    //Actual work to be done by logout button
    //requestStackPop();
    //requestStackPush(States::ID::LoginState);

}

void AdminState::selectedSlot(int i, int c)
{
    //Populates the data fields with data from selected row
    QString s;

    this->ui->idLine->setText(characterVect.at(i).userID);
    this->ui->usernameLine->setText(characterVect.at(i).username);
    this->ui->passwordLine->setText(characterVect.at(i).password);
    s = QString::number(characterVect.at(i).currentLevel);
    this->ui->cLevelLine->setText(s);
    s = QString::number(characterVect.at(i).currentQuest);
    this->ui->cQuestLine->setText(s);
    s = QString::number(characterVect.at(i).currentProgress);
    this->ui->cProgressLine->setText(s);

    //Sets the master number index for deletion
    masterNum = i;
}

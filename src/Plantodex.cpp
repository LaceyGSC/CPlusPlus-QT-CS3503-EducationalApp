#include "Plantodex.h"
#include "ui_Plantodex.h"
#include <sstream>

Plantodex::Plantodex(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plantodex)
{
    ui->setupUi(this);
}

Plantodex::~Plantodex()
{
    delete list;
    delete ui;
}

void Plantodex::getPlantNames(std::vector<QString> book)
{
    for(uint n = 0; n < book.size(); n = n+5)
    {
        plantNames.push_back(book[n]);
        plantNames.push_back(";");
    }
}

void Plantodex::setUpPlantodex(QString *string)
{
    std::istringstream ss(string->toStdString());
    std::string tok;

    while(getline(ss, tok, '\n'))
    {
        book.push_back(QString::fromStdString(tok));
    }

    getPlantNames(book);
    updatePlantodex(0);

    list->setStringList(plantNames.split(";"));

    ui->plantListView->setModel(list);
}

void Plantodex::updatePlantodex(int index)
{
    ui->commonNameLabel->setText(book[index]);
    ui->scietificNameLabel->setText(book[index+1]);
    ui->descriptionText->setText(book[index+2]);
    ui->usesText->setText(book[index+3]);
    ui->typeLabel->setText(book[index+4]);
}

void Plantodex::on_plantListView_clicked(const QModelIndex &index)
{
    updatePlantodex(index.row()*5);
}

#include "Plantodex.h"
#include "ui_Plantodex.h"

Plantodex::Plantodex(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plantodex)
{
    ui->setupUi(this);
}

Plantodex::~Plantodex()
{
    delete ui;
}

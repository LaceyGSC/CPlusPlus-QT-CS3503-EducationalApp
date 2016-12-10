#include "QuickPlantAnalyzer.h"
#include "ui_QuickPlantAnalyzer.h"

QuickPlantAnalyzer::QuickPlantAnalyzer(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::QuickPlantAnalyzer)
{
    mUi->setupUi(this);
}

QuickPlantAnalyzer::~QuickPlantAnalyzer()
{
    delete mUi;
}

#include "ManualDialog.h"
#include "ui_ManualDialog.h"

ManualDialog::ManualDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::ManualDialog)
{
    mUi->setupUi(this);
}

ManualDialog::~ManualDialog()
{
    delete mUi;
}

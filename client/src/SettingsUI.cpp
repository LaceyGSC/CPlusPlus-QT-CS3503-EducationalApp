#include "SettingsUI.h"
#include "ui_SettingsUI.h"

SettingsUI::SettingsUI(GameState::GameContext context, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::SettingsUI)
    , mGameContext(context)
{
    mUi->setupUi(this);

    connect(mUi->quickTurn, SIGNAL(toggled(bool)), this, SLOT(toggleFastTurn(bool)));

    mUi->quickTurn->setChecked(true);
}

SettingsUI::~SettingsUI()
{
    delete mUi;
}

void SettingsUI::toggleFastTurn(bool toggle)
{
    mGameContext.settings.quickTurn = toggle;
}

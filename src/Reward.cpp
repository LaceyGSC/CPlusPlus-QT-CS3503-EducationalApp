#include "Reward.h"
#include "ui_Reward.h"

Reward::Reward(const QString &desc, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Reward)
    , mActivateCallback()
    , mDeactivateCallback()
    , mReaped(false)
{
    mUi->setupUi(this);
    mUi->rewardLabel->setText(desc);

    mUi->formLayout->setAlignment(mUi->checkBox, Qt::AlignRight);

    mUi->checkBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    mUi->checkBox->setFocusPolicy(Qt::NoFocus);

    show();
}

Reward::~Reward()
{
    delete mUi;
}

void Reward::setOnActivate(const std::function<void()>& callback)
{
    mActivateCallback = callback;
}

void Reward::setOnDeactivate(const std::function<void()>& callback)
{
    mDeactivateCallback = callback;
}

void Reward::activate()
{
    if (mActivateCallback)
    {
        if (!mReaped)
        {
            mActivateCallback();
            mUi->checkBox->setChecked(true);
            mReaped = true;
        }
    }
}

void Reward::deactivate()
{
    if (mDeactivateCallback)
    {
        if (mReaped)
        {
            mDeactivateCallback();
            mUi->checkBox->setChecked(false);
            mReaped = false;
        }
    }
}

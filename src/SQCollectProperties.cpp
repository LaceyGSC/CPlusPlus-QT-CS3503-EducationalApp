#include "SQCollectProperties.h"

#include "Quest.h"

SQCollectProperties::SQCollectProperties(const QString &desc, Plant::Properties prop, int actual, QWidget *parent)
    : SubQuest(parent)
    , mProp(prop)
    , mActual(actual)
    , mCollected(0)
{
    mDesc.setText(desc);

    mBar.setMinimumSize(QSize(80, 21));
    mBar.setMaximumSize(QSize(80, 21));
    mBar.setMaximum(mActual);
    mBar.setValue(mCollected);
    mBar.setAlignment(Qt::AlignCenter);
    mBar.setFormat(QString("%v/") + QString::number(mActual));
    mBar.show();

    mDesc.setWordWrap(true);
    mDesc.show();

    getLayout()->addWidget(&(mDesc));
    getLayout()->addWidget(&(mBar));
}

void SQCollectProperties::update(Command *command)
{
    if (command->commandType == CommandType::ID::PickUp)
    {
        auto derivedCommand = dynamic_cast<PickUp*>(command);

        if (derivedCommand->amount > 0)
        {
            if (mProp & derivedCommand->prop && mCollected < mActual)
            {
                if (mCollected + derivedCommand->amount > mActual)
                    // Clamp
                    mCollected = mActual;
                else
                    mCollected += derivedCommand->amount;

                mBar.setValue(mCollected);
            }
        }
        else if (derivedCommand->amount < 0)
        {
            if (mProp & derivedCommand->prop && mCollected >= 0)
            {
                if (mCollected - derivedCommand->amount < 0)
                    // Clamp
                    mCollected = 0;
                else
                    mCollected -= derivedCommand->amount;

                mBar.setValue(mCollected);
            }
        }

        mCompleted = (mCollected == mActual);
    }
}


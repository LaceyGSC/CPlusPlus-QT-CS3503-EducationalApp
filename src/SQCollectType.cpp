#include "SQCollectType.h"

#include "Quest.h"

SQCollectType::SQCollectType(const QString &desc, int collectedTypes, int actualTypes, GameState::GameContext gameContext, QWidget *parent)
    : SubQuest(gameContext, parent)
    , mCollectedTypes()
    , mCollected(0)
    , mActualTypes(actualTypes)
{
    mDesc.setText(desc);

    mBar.setMinimumSize(QSize(80, 21));
    mBar.setMaximumSize(QSize(80, 21));
    mBar.setMaximum(mActualTypes);
    mBar.setValue(mCollectedTypes.size());
    mBar.setAlignment(Qt::AlignCenter);
    mBar.setFormat(QString("%v/") + QString::number(mActualTypes));
    mBar.show();

    mDesc.setWordWrap(true);
    mDesc.show();

    getLayout()->addWidget(&(mDesc));
    getLayout()->addWidget(&(mBar));

    if (collectedTypes > 0)
    {
        if (mCollected + collectedTypes > mActualTypes)
            // Clamp
            mCollected = mActualTypes;
        else
            mCollected = collectedTypes;

        mBar.setValue(mCollected + mCollectedTypes.size());
        mCompleted = (mCollectedTypes.size() + mCollected == mActualTypes);
    }
}

void SQCollectType::update(Command *command)
{
    if (!mCompleted)
    {
        if (command->commandType == CommandTypes::ID::PickUp)
        {
            auto derivedCommand = dynamic_cast<PickUp*>(command);

            mCollectedTypes.insert(derivedCommand->tileId);
            mBar.setValue(mCollectedTypes.size() + mCollected);

            mCompleted = (mCollectedTypes.size() + mCollected == mActualTypes);
        }
    }
}


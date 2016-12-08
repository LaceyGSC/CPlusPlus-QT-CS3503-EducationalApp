#include "SQCollectType.h"

#include "Quest.h"

SQCollectType::SQCollectType(const QString &desc, int actualTypes, QWidget *parent)
    : SubQuest(parent)
    , mCollectedTypes()
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
}

void SQCollectType::update(Command *command)
{
    if (command->commandType == CommandType::ID::PickUp)
    {
        auto derivedCommand = dynamic_cast<PickUp*>(command);

        mCollectedTypes.insert(derivedCommand->plantId);
        mBar.setValue(mCollectedTypes.size());

        mCompleted = (mCollectedTypes.size() == mActualTypes);
    }
}


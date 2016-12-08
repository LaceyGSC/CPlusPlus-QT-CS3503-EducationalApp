#include "SQCollectType.h"

#include "Quest.h"

SQCollectType::Data::Data(const QString &desc, int actualTypes)
    : collectedTypes()
    , actualTypes(actualTypes)
    , desc()
    , bar()
{
    this->desc.setText(desc);
}

SQCollectType::SQCollectType(SQCollectType::DataPtr data, QWidget *parent)
    : SubQuest(parent)
    , mData(std::move(data))
{
    mData->desc.setParent(this);
    mData->bar.setParent(this);

    mData->bar.setMinimumSize(QSize(80, 21));
    mData->bar.setMaximumSize(QSize(80, 21));
    mData->bar.setMaximum(mData->actualTypes);
    mData->bar.setValue(mData->collectedTypes.size());
    mData->bar.setAlignment(Qt::AlignCenter);
    mData->bar.setFormat(QString("%v/") + QString::number(mData->actualTypes));
    mData->bar.show();

    mData->desc.setWordWrap(true);
    mData->desc.show();

    getLayout()->addWidget(&(mData->desc));
    getLayout()->addWidget(&(mData->bar));
}

void SQCollectType::update(Command *command)
{
    if (command->commandType == CommandType::ID::PickUp)
    {
        auto derivedCommand = dynamic_cast<PickUp*>(command);

        mData->collectedTypes.insert(derivedCommand->plantId);
        mData->bar.setValue(mData->collectedTypes.size());
    }
}


#include "SQCollectProperties.h"

#include "Quest.h"

SQCollectProperties::Data::Data(const QString &desc, Plant::Properties prop, int actual)
    : prop(prop)
    , actual(actual)
    , collected(0)
    , desc()
    , bar()
{
    this->desc.setText(desc);
}

SQCollectProperties::SQCollectProperties(SQCollectProperties::DataPtr data, QWidget *parent)
    : SubQuest(parent)
    , mData(std::move(data))
{
    mData->desc.setParent(this);
    mData->bar.setParent(this);

    mData->bar.setMinimumSize(QSize(80, 21));
    mData->bar.setMaximumSize(QSize(80, 21));
    mData->bar.setMaximum(mData->actual);
    mData->bar.setValue(mData->collected);
    mData->bar.setAlignment(Qt::AlignCenter);
    mData->bar.setFormat(QString("%v/") + QString::number(mData->actual));
    mData->bar.show();

    mData->desc.setWordWrap(true);
    mData->desc.show();

    getLayout()->addWidget(&(mData->desc));
    getLayout()->addWidget(&(mData->bar));
}

void SQCollectProperties::update(Command *command)
{
    if (command->commandType == CommandType::ID::PickUp)
    {
        auto derivedCommand = dynamic_cast<PickUp*>(command);

        if (derivedCommand->amount > 0)
        {
            if (mData->prop & derivedCommand->prop && mData->collected < mData->actual)
            {
                if (mData->collected + derivedCommand->amount > mData->actual)
                    // Clamp
                    mData->collected = mData->actual;
                else
                    mData->collected += derivedCommand->amount;

                mData->bar.setValue(mData->collected);
            }
        }
        else if (derivedCommand->amount < 0)
        {
            if (mData->prop & derivedCommand->prop && mData->collected >= derivedCommand->amount)
            {
                if (mData->collected - derivedCommand->amount < 0)
                    // Clamp
                    mData->collected = 0;
                else
                    mData->collected -= derivedCommand->amount;

                mData->bar.setValue(mData->collected);
            }
        }
    }
}


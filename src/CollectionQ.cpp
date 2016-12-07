#include "CollectionQ.h"

#include <cassert>
#include <utility>

CollectionQ::Data::Data(int actual, QGridLayout *containerLayout, QWidget *parent)
    : actual(actual)
    , collected(0)
    , bar(parent)
    , desc(parent)
{
    bar.setMinimumSize(QSize(80, 21));
    bar.setMaximumSize(QSize(80, 21));
    bar.setMaximum(actual);
    bar.setValue(collected);
    bar.setAlignment(Qt::AlignCenter);
    bar.setFormat("%v/" + actual);

    desc.setWordWrap(true);

    containerLayout->addWidget(&bar, 0, 1, 1, 1);
    containerLayout->addWidget(&desc, 1, 0, 1, 2);


          /*progressBar = new QProgressBar(Quest);
          progressBar->setObjectName(QStringLiteral("progressBar"));
          progressBar->setMinimumSize(QSize(80, 21));
          progressBar->setMaximumSize(QSize(80, 21));
          progressBar->setValue(0);
          progressBar->setAlignment(Qt::AlignCenter);

          gridLayout->addWidget(progressBar, 0, 1, 1, 1);

          progressBar->setFormat(QApplication::translate("Quest", "%p%", 0));

              description = new QLabel(Quest);
              description->setObjectName(QStringLiteral("description"));
              description->setFrameShape(QFrame::Box);
              description->setFrameShadow(QFrame::Sunken);
              description->setWordWrap(true);

              gridLayout->addWidget(description, 1, 0, 1, 2);*/
}

CollectionQ::CollectionQ(const QString &title, const QString &description, QWidget *parent)
    : Quest(title, description, parent)
    , mCollectionData()
{
}

void CollectionQ::addData(Plant::ID id, CollectionQ::Ptr data)
{
    auto inserted = mCollectionData.insert(std::make_pair(id, std::move(data)));
    assert(inserted.second);
}

void CollectionQ::update(Command command)
{
    /*if (command.commandId == CommandType::ID::PickUp)
    {
        PickUp command = static_cast<PickUp>(command);
        if (mCollectionData.find(command.plantId) != mCollectionData.end())
        {
            if (command.amount > 0)
            {
                if (mActualData[command.plantId] != mCollectionData[command.plantId])
                    mActualData[command.plantId] += command.amount;
            }
            else if (command.amount < 0)
            {
                if (mActualData[command.plantId] != 0)
                    mActualData[command.plantId] -= command.amount;
            }
        }
    }

    int collectionAmount = 0;

    for (auto &it : mCollectionData)
        collectionAmount += mCollectionData[it.first];

    int actualAmount = 0;

    for (auto &it : mActualData)
        actualAmount += mActualData[it.first];

    setCompletion((float)actualAmount / collectionAmount * 100);*/
}

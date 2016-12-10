#ifndef QUEST_H
#define QUEST_H

#include <QWidget>
#include <QString>
#include <QGridLayout>

#include "Commands.h"

#include <vector>
#include <memory>
#include <functional>

namespace Ui {
class Quest;
}

class SubQuest;

class Quest : public QWidget
{
    Q_OBJECT
public:
    typedef std::unique_ptr<SubQuest> SubQuestPtr;

public:
    // The parent should be of type Level
    explicit Quest(const QString &title, QWidget *parent = 0);
    ~Quest();

    void addSubQuest(SubQuestPtr subQuest);

    void update(Command *command);

    QGridLayout* getLayout() const;

    bool isCompleted() const;

    void setHashId(int value);
    int getHashId() const;

    const std::vector<Quest::SubQuestPtr>& getSubQuests() const;

private:
    Ui::Quest *mUi;

    std::vector<Quest::SubQuestPtr> mSubQuests;

    // Used for hashing
    int mHashId;
};

// Defining custom std::hash for QuestPtr. This allows for the use of
// stl containers that require a hash function (such as std::unordered_map,
// which requires the key to have a hash function). Courtesy of :
// http://stackoverflow.com/questions/18098178/how-do-i-use-unordered-set

template<>
struct std::hash<Quest*>
{
    std::size_t operator()(std::unique_ptr<Quest> const &questPtr) const noexcept
    {
        return std::hash<int>()(questPtr->getHashId());
    }
};

#endif // QUEST_H

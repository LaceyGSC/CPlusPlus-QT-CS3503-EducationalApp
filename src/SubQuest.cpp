#include "SubQuest.h"

#include "Quest.h"

#include <utility>

SubQuest::SubQuest(QWidget *parent)
    : QWidget(parent)
{
    show();
}

QGridLayout* SubQuest::getLayout() const
{
    return dynamic_cast<Quest*>(parent())->getLayout();
}

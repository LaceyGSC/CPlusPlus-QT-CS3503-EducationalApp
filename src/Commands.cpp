#include "Commands.h"

Command::Command(CommandType::ID id)
    : commandType(id)
{
}

Command::~Command()
{
}

PickUp::PickUp(Plant::ID id, Plant::Properties prop, int amount)
    : Command(CommandType::ID::PickUp)
    , plantId(id)
    , prop(prop)
    , amount(amount)
{
}

Move::Move(Movement::Direction dir, int steps)
    : Command(CommandType::ID::Move)
    , dir(dir)
    , steps(steps)
{
}

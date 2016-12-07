#include "Commands.h"

Command::Command(CommandType::ID id)
{
}

PickUp::PickUp(Plant::ID id, int amount)
    : Command(CommandType::ID::PickUp)
    , plantId(id)
    , amount(amount)
{
}

Move::Move(Movement::Direction dir, int steps)
    : Command(CommandType::ID::Move)
    , dir(dir)
    , steps(steps)
{
}

#include "Commands.h"

Command::Command(CommandTypes::ID id)
    : commandType(id)
{
}

Command::~Command()
{
}

PickUp::PickUp(Tiles::ID id, int amount)
    : Command(CommandTypes::ID::PickUp)
    , tileId(id)
    , amount(amount)
{
}

Move::Move(Directions::ID dir, int steps)
    : Command(CommandTypes::ID::Move)
    , dir(dir)
    , steps(steps)
{
}

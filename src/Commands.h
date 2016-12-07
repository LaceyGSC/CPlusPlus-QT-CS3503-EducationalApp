#ifndef COMMAND_H
#define COMMAND_H

#include "CommandTypeIdentifiers.h"
#include "PlantIdentifiers.h"
#include "MovementIdentifiers.h"

struct Command
{
    Command(CommandType::ID id = CommandType::ID::None);

    CommandType::ID commandId;
};

struct PickUp : public Command
{
    PickUp(Plant::ID id, int amount);

    Plant::ID plantId;
    int amount;
};

struct Move : public Command
{
    Move(Movement::Direction dir, int steps);

    Movement::Direction dir;
    int steps;
};

#endif // COMMAND_H

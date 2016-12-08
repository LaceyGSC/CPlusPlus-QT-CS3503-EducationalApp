#ifndef COMMAND_H
#define COMMAND_H

#include "CommandTypeIdentifiers.h"
#include "PlantIdentifiers.h"
#include "MovementIdentifiers.h"

struct Command
{
    Command(CommandType::ID id = CommandType::ID::None);

    // Makes this class a polymorphic base so that we can use dynamic_cast
    // to cast it to a derived struct
    virtual ~Command();

    CommandType::ID commandType;
};

struct PickUp : public Command
{
    PickUp(Plant::ID id, Plant::Properties prop, int amount);

    Plant::ID plantId;
    Plant::Properties prop;
    int amount;
};

struct Move : public Command
{
    Move(Movement::Direction dir, int steps);

    Movement::Direction dir;
    int steps;
};

#endif // COMMAND_H

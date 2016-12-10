#ifndef COMMAND_H
#define COMMAND_H

#include "Identifiers.h"

struct Command
{
    Command(CommandTypes::ID id = CommandTypes::ID::None);

    // Makes this class a polymorphic base so that we can use dynamic_cast
    // to cast it to a derived struct
    virtual ~Command();

    CommandTypes::ID commandType;
};

struct PickUp : public Command
{
    PickUp(Tiles::ID id, int amount);

    Tiles::ID tileId;
    int amount;
};

struct Move : public Command
{
    Move(Directions::ID dir, int steps);

    Directions::ID dir;
    int steps;
};

#endif // COMMAND_H

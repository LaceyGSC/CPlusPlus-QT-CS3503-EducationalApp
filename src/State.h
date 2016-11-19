/*
 * Author: King Hoe Wong
 * Desc: Abstract class for a state in the game. A state is a QWidget. It should be
 *       used to display a "state" in the game. E.g. states: Splash screen state,
 *       menu state, play state, pause state, game over state, etc.
 *
 */

#ifndef STATE_H
#define STATE_H

#include <QWidget>
#include <SFML/System.hpp>

#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <memory>

// Forward declaration
class StateStack;

class State : public QWidget
{
public:
    typedef std::unique_ptr<State> Ptr;

public:
    // Context allows the states to get resources from the resource managers
    struct Context
    {
                        Context(TextureManager &textures);

        TextureManager  &textures;
    };

public:
                        State(StateStack &stack, Context &context, QWidget *parent = 0);

    // For updating game logic. Returns a bool so that only certain states get
    // updated (E.g.: returning false with a pause state on top of a play state will
    // cease all updates to the play state and hence, actually "stopping" the play state)
    virtual bool        update(const sf::Time &deltaTime) = 0;

    // The reason for the requests is so that the state stack container
    // doesn't get changed while it is being iterated through
    void                requestStackPush(States::ID stateID);
    void                requestStackPop();
    void                requestStackClear();

    Context             getContext() const;

private:
    // Need a pointer to the stack so that requests can be made
    StateStack          *mStateStack;
    Context             mContext;
};

#endif // STATE_H
/*
 * Author: King Hoe Wong
 * Desc: Implementation of State class.
 *
 */

#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, QWidget *parent)
    : QWidget(parent)
    , mStateStack(&stack)
{
}

void State::requestStackPush(States::ID stateID)
{
    mStateStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStateStack->popState();
}

void State::requestStackClear()
{
    mStateStack->clearStates();
}

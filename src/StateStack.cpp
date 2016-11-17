/*
 * Author: King Hoe Wong
 * Desc: Implementation for the StateStack class.
 *
 */

#include <SFML/System.hpp>

#include "StateStack.h"

#include <cassert>

StateStack::StateStack()
    : mStack()
    , mPendingList()
    , mFactories()
{
}

void StateStack::update(const sf::Time &deltaTime)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++)
        // if update() returns false, the remaining updates will
        // be skipped
        if (!(*it)->update(deltaTime))
            break;

    // Process requests only after the iteration is done
    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
    mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

// Assert failure if state is not found
State::Ptr StateStack::getState(States::ID stateID) const
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (PendingChange& pendingChange : mPendingList)
    {
        switch (pendingChange.action)
        {
        case Action::Push:
            mStack.push_back(getState(pendingChange.stateID));
            break;
        case Action::Pop:
            mStack.pop_back();
            break;
        case Action::Clear:
            mStack.clear();
            break;
        }
    }
    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action)
    , stateID(stateID)
{
}

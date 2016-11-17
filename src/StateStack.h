/*
 * Author: King Hoe Wong
 * Desc: Represents a finite state machine for the game. Controls
 *       the states of the game.
 *
 */

#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.h"

#include <QWidget>
#include <QLayout>
#include <SFML/System.hpp>

#include <vector>
#include <functional>
#include <unordered_map>

// sf::NonCopyable is SFML's singleton class. We only want a single copy of StateStack
class StateStack : private sf::NonCopyable
{
private:
    // This is one long ass declaration
    typedef std::unordered_map<States::ID, std::function<State::Ptr()>> FactoryMap;

public:
    explicit                    StateStack(State::Context context);

    // Registers the state with its declaration function into an unordered map. This
    // allows for the factory method pattern which can easily create varying states
    template <typename StateType>
    void						registerState(States::ID stateID, QLayout *layout, QWidget *parent = 0);

    // Updates game logic. Propagates an update call to all its children (states)
    void						update(const sf::Time &deltaTime);

    void    					pushState(States::ID stateID);
    void						popState();
    void						clearStates();

    bool						isEmpty() const;

private:
    // A state is always assumed to have existed. Method will assert failure if state is not found
    State::Ptr                  getState(States::ID stateID) const;

    // For pending changes
    void						applyPendingChanges();

private:
    // Defines the actions for pending changes
    enum class Action { Push, Pop, Clear };

    // A struct to store the requests requested by the states. The reason for this is to prevent
    // conflict while the stack is iterating through its states.
    struct PendingChange
    {
        explicit                PendingChange(Action action, States::ID stateID = States::ID::None);

        Action                  action;
        States::ID              stateID;
    };

private:
    // The state stack
    std::vector<State::Ptr>     mStack;

    // List of pending requests
    std::vector<PendingChange>  mPendingList;

    // The reason for using State::Ptr (a pointer to a state) is to get around
    // std::function trying to instantiate an abstract class
    FactoryMap                  mFactories;

    // Context allows the states to get resources from the resource managers
    State::Context              mContext;
};

// Factory function
template <typename StateType>
void StateStack::registerState(States::ID stateID, QLayout *layout, QWidget *parent)
{
    mFactories[stateID] = [this, parent, layout] ()
    {
        State::Ptr state(new StateType(*this, mContext, parent));

        // We want to add the state widget to the main layout so that it is centered and expands
        // to the size of the main window.
        layout->addWidget(&static_cast<QWidget&>(*state));
        return state;
    };
}

#endif // STATESTACK_H

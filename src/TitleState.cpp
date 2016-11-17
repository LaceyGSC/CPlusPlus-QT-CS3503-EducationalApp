/*
 * Author: King Hoe Wong
 * Desc: Implementation for TitleState.
 *
 */

#include "TitleState.h"
#include "ui_TitleState.h"

#include <QWidget>

#include "State.h"
#include "StateStack.h"

TitleState::TitleState(StateStack &stack, QWidget *parent)
    : State(stack, parent)
    , mUi(new Ui::TitleState)
{
    mUi->setupUi(this);

    // Display the widget
    this->show();
}

TitleState::~TitleState()
{
    delete mUi;
}


bool TitleState::update(const sf::Time &deltaTime)
{
    return true;
}

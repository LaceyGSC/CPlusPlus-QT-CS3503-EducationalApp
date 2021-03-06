/*
 * Author: King Hoe Wong
 * Desc: Implementation of State class.
 *
 */

#include "State.h"
#include "StateStack.h"

#include "Identifiers.h"

State::Context::Context(TextureManager &textures, FontManager &fonts, SoundPlayer &sounds, MusicPlayer &music, ServerConnection &connection)
    : textures(textures)
    , fonts(fonts)
    , sounds(sounds)
    , music(music)
    , connection(connection)
{
}

State::State(StateStack &stack, Context &context, QWidget *parent)
    : QWidget(parent)
    , mStateStack(&stack)
    , mContext(context)
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

State::Context State::getContext() const
{
    return mContext;
}

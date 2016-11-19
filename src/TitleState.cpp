/*
 * Author: King Hoe Wong
 * Desc: Implementation for TitleState.
 *
 */

#include "TitleState.h"
#include "ui_TitleState.h"

#include <SFML/Graphics.hpp>
#include <QWidget>

#include "State.h"
#include "StateStack.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "SFMLCanvas.h"

TitleState::TitleState(StateStack &stack, Context &context, QWidget *parent)
    : State(stack, context, parent)
    , mUi(new Ui::TitleState)
    , mCanvas(QPoint(0, 0), QSize(parent->size().width() / 2, parent->size().height()), context, this)
{
    mUi->setupUi(this);

    // Display the title state widget
    this->show();

    QObject::connect(mUi->pushButton, SIGNAL(pressed()), this, SLOT(start()));
    mCanvas.hide();
}

TitleState::~TitleState()
{
    delete mUi;
}


bool TitleState::update(const sf::Time &deltaTime)
{
    return true;
}

void TitleState::start()
{
    if (mCanvas.isHidden())
    {
        mUi->horizontalLayout->addWidget((QWidget*)(&mCanvas));
        mCanvas.show();
    }
    else
    {
        mUi->horizontalLayout->removeWidget((QWidget*)(&mCanvas));
        mCanvas.hide();
    }
}

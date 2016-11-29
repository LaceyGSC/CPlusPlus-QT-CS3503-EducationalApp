#include "Character.h"
#include <QResizeEvent>
#include <QSize>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

#include <iostream>
using namespace sf;
Character::Character(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
{
}

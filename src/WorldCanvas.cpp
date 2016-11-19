/*
 * Author: King Hoe Wong
 * Desc: Implementation for WorldCanvas class.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "WorldCanvas.h"

#include <QResizeEvent>
#include <QSize>
#include <SFML/Graphics.hpp>

#include "State.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

#include <iostream>

WorldCanvas::WorldCanvas(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
{
}

void WorldCanvas::onInit()
{
    // Load texture and initialize sprite with texture.
    getContext().textures.load(static_cast<int>(Textures::ID::Default), "qrc:/../media/Textures/default.png");
    getContext().textures.get(static_cast<int>(Textures::ID::Default)).setSmooth(true);

    mSprite.setTexture(getContext().textures.get(static_cast<int>(Textures::ID::Default)));
    mSprite.setPosition(0.f, 0.f);
    mSprite.scale(0.5f, 0.5f);
}

void WorldCanvas::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
    // Draw sprite
    target.draw(mSprite, states);
    //std::cout << mSprite.getPosition().x << ": " << mSprite.getPosition().y << std::endl;
}

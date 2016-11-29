/*
 * Author: King Hoe Wong
 * Desc: Implementation for World class.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "World.h"

#include <QResizeEvent>
#include <QSize>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

#include <iostream>

using namespace sf;
World::World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
{
}

void World::onInit()
{
    // Load texture and initialize sprite with texture.
    getContext().textures.load(static_cast<int>(Textures::ID::Default), "qrc:/../media/Textures/default.png");
    getContext().textures.get(static_cast<int>(Textures::ID::Default)).setSmooth(true);

    mSprite.setTexture(getContext().textures.get(static_cast<int>(Textures::ID::Default)));
    mSprite.setPosition(0.f, 0.f);
    mSprite.scale(0.5f, 0.5f);


}

void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
    // Draw sprite
    target.draw(mSprite, states);

    if(Keyboard::isKeyPressed(Keyboard::Right)){
        mSprite.move(1,0);
       //  mSprite.setPosition(mSprite.getPosition().x+1,mSprite.getPosition().y);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Left)){
         mSprite.setPosition(mSprite.getPosition().x-1,mSprite.getPosition().y);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Up)){
         mSprite.setPosition(mSprite.getPosition().x,mSprite.getPosition().y-1);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Down)){
         mSprite.setPosition(mSprite.getPosition().x,mSprite.getPosition().y+1);
    }
}

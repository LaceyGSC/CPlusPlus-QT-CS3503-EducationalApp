#include "Character.h"
#include <QResizeEvent>
#include <QSize>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

#include <iostream>
using namespace sf;
//Character::Character(const QPoint &pos, const QSize &size, State::Context context, QWidget *parent)
//    : QSFMLWidget(pos, size, &context, parent)
//{
//}

//void World::onInit()
//{
//    // Load texture and initialize sprite with texture.
//    getContext().textures.load(static_cast<int>(Textures::ID::Default), "qrc:/../media/Textures/meme.png");
//    getContext().textures.get(static_cast<int>(Textures::ID::Default)).setSmooth(true);

//    mSprite.setTexture(getContext().textures.get(static_cast<int>(Textures::ID::Default)));
//    mSprite.setPosition(0.f, 0.f);
//    mSprite.scale(0.5f, 0.5f);


//}

//void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
//{
//    // Draw sprite
//    target.draw(mSprite, states);
//    if(Keyboard::isKeyPressed(Keyboard::Right)){
//        mSprite.move(0.1,0);
//    }
//    else if(Keyboard::isKeyPressed(Keyboard::Left)){
//        mSprite.move(-0.1,0);
//    }
//    else if(Keyboard::isKeyPressed(Keyboard::Up)){
//          mSprite.move(0,-0.1);
//    }
//    else if(Keyboard::isKeyPressed(Keyboard::Down)){
//         mSprite.move(0,0.1);
//    }
//}


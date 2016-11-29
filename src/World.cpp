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

World::World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
{
                map.setRefSize(512);;
}

void World::onInit()
{
    // Load texture and initialize sprite with texture.
    getContext().textures.load(static_cast<int>(Textures::ID::Default), "qrc:/../media/Textures/default.png");
    getContext().textures.get(static_cast<int>(Textures::ID::Default)).setSmooth(true);

    int iter = 1;
    getContext().textures.load(1, "qrc:/../media/Textures/Bridge.png");
    getContext().textures.get(1).setSmooth(true);

    getContext().textures.load(2, "qrc:/../media/Textures/DeepFreshWater.png");
    getContext().textures.get(2).setSmooth(true);

    getContext().textures.load(3, "qrc:/../media/Textures/DeepSaltWater.png");
    getContext().textures.get(3).setSmooth(true);

    getContext().textures.load(4, "qrc:/../media/Textures/Dirt.png");
    getContext().textures.get(4).setSmooth(true);

    getContext().textures.load(5, "qrc:/../media/Textures/Fire.png");
    getContext().textures.get(5).setSmooth(true);

    getContext().textures.load(6, "qrc:/../media/Textures/Grass.png");
    getContext().textures.get(6).setSmooth(true);

    getContext().textures.load(7, "qrc:/../media/Textures/Mountain.png");
    getContext().textures.get(7).setSmooth(true);

    getContext().textures.load(8, "qrc:/../media/Textures/QuickSand.png");
    getContext().textures.get(8).setSmooth(true);

    getContext().textures.load(9, "qrc:/../media/Textures/RedSand.png");
    getContext().textures.get(9).setSmooth(true);

    getContext().textures.load(10, "qrc:/../media/Textures/Sand.png");
    getContext().textures.get(10).setSmooth(true);

    getContext().textures.load(11, "qrc:/../media/Textures/ShallowFreshWater.png");
    getContext().textures.get(11).setSmooth(true);

    getContext().textures.load(12, "qrc:/../media/Textures/ShallowSaltWater.png");
    getContext().textures.get(12).setSmooth(true);

    getContext().textures.load(13, "qrc:/../media/Textures/Tree.png");
    getContext().textures.get(13).setSmooth(true);

    mSprite.setTexture(getContext().textures.get(static_cast<int>(Textures::ID::Default)));
    mSprite.setPosition(0.f, 0.f);
    mSprite.scale(0.5f, 0.5f);
}

void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
    // Draw sprite
    target.draw(mSprite, states);

    target.clear();
    for(int x = 0;x<1280;x+=32)
    {
        for(int y = 0;y<1280;y+=32)
        {

            int type = (map.getValue(mWorldLocation.x()+x/32+0,mWorldLocation.y()+y/32+0)%12 )+1;
            mSprite.setTexture(getContext().textures.get(type));
            mSprite.setPosition(x,y);
            mSprite.setScale(1.0,1.0);
            target.draw(mSprite, states);
        }
    }
}

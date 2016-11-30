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
                map.setRefSize(512);;
}

void World::onInit()
{
    // Load texture and initialize sprite with texture.
    getContext().textures.load(static_cast<int>(Textures::ID::Default), "qrc:/../media/Textures/default.png");
    getContext().textures.get(static_cast<int>(Textures::ID::Default)).setSmooth(true);

    WorldLoader(0);

    mSprite.setTexture(getContext().textures.get(static_cast<int>(Textures::ID::Default)));
    mSprite.setPosition(0.f, 0.f);
    mSprite.scale(0.5f, 0.5f);


}

void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
    std::complex<float> temp = mWorldLocation;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        temp +=std::complex<float>(0.2,0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        temp +=std::complex<float>(-0.2,0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        temp +=std::complex<float>(0,-0.2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        temp +=std::complex<float>(0,0.2);
    }


    if(moveValid(temp)){
        clear();
        mWorldLocation = temp;
        DrawMap(target,states);
    }
}

void World::WorldLoader(int worldtype)
{

    if(worldtype==0)
    {
        map.setJuliaValue(std::complex<double>(-.621,0));
        getContext().textures.load(1, "qrc:/../media/Textures/Bridge.png");
        getContext().textures.load(2, "qrc:/../media/Textures/DeepFreshWater.png");
        getContext().textures.load(3, "qrc:/../media/Textures/DeepSaltWater.png");
        getContext().textures.load(4, "qrc:/../media/Textures/Dirt.png");
        getContext().textures.load(5, "qrc:/../media/Textures/Fire.png");
        getContext().textures.load(6, "qrc:/../media/Textures/Grass.png");
        getContext().textures.load(7, "qrc:/../media/Textures/Mountain.png");
        getContext().textures.load(8, "qrc:/../media/Textures/QuickSand.png");
        getContext().textures.load(9, "qrc:/../media/Textures/RedSand.png");
        getContext().textures.load(10, "qrc:/../media/Textures/Sand.png");
        getContext().textures.load(11, "qrc:/../media/Textures/ShallowFreshWater.png");
        getContext().textures.load(12, "qrc:/../media/Textures/ShallowSaltWater.png");
        getContext().textures.load(13, "qrc:/../media/Textures/Tree.png");
        landcount = 12;
    }
    else if(worldtype==1)
    {
        map.setJuliaValue(std::complex<double>(-.5,.002));
        getContext().textures.load(1, "qrc:/../media/Textures/Dirt.png");
        getContext().textures.load(2, "qrc:/../media/Textures/Grass.png");
        getContext().textures.load(3, "qrc:/../media/Textures/Mountain.png");
        getContext().textures.load(4, "qrc:/../media/Textures/Grass.png");
        getContext().textures.load(5, "qrc:/../media/Textures/Mountain.png");
        getContext().textures.load(6, "qrc:/../media/Textures/Sand.png");
        getContext().textures.load(7, "qrc:/../media/Textures/ShallowFreshWater.png");
        getContext().textures.load(8, "qrc:/../media/Textures/ShallowSaltWater.png");
        getContext().textures.load(9, "qrc:/../media/Textures/Tree.png");
        getContext().textures.load(10, "qrc:/../media/Textures/Tree.png");
        landcount = 9;
    }
    else if(worldtype==2){
        map.setJuliaValue(std::complex<double>(-.5,-.002));
        getContext().textures.load(1, "qrc:/../media/Textures/Dirt.png");
        getContext().textures.load(2, "qrc:/../media/Textures/Fire.png");
        getContext().textures.load(3, "qrc:/../media/Textures/Grass.png");
        getContext().textures.load(4, "qrc:/../media/Textures/Mountain.png");
        getContext().textures.load(5, "qrc:/../media/Textures/QuickSand.png");
        getContext().textures.load(6, "qrc:/../media/Textures/RedSand.png");
        getContext().textures.load(7, "qrc:/../media/Textures/Sand.png");
        getContext().textures.load(8, "qrc:/../media/Textures/QuickSand.png");
        getContext().textures.load(9, "qrc:/../media/Textures/RedSand.png");
        getContext().textures.load(10, "qrc:/../media/Textures/Sand.png");
        getContext().textures.load(11, "qrc:/../media/Textures/ShallowFreshWater.png");
        getContext().textures.load(12, "qrc:/../media/Textures/Tree.png");
        landcount = 11;
    }
    else {

    }
}
void World::DrawMap(sf::RenderTarget& target, sf::RenderStates states)
{
    target.clear();
    float scale = 2;
    int jumpgap = 32*scale;
    for(int x = 0;x<640*scale;x+=jumpgap)
    {
        for(int y = 0;y<640*scale;y+=jumpgap)
        {
            int type = (map.getValue(static_cast<int>(mWorldLocation.real())+x/jumpgap+0,static_cast<int>(mWorldLocation.imag())+y/jumpgap+0)%landcount )+1;
            mSprite.setTexture(getContext().textures.get(type));
            mSprite.setPosition(x,y);
            mSprite.setScale(scale,scale);
            target.draw(mSprite, states);
        }
    }
}

bool World::moveValid(std::complex<float> next)
{
    return true;
}

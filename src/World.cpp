/*
 * Author: King Hoe Wong
 * Desc: Implementation for World class.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "World.h"

#include <QResizeEvent>
#include <QSize>
#include <QQueue>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

#include <iostream>

using namespace sf;
World::World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent),characterRelativePos(std::complex<double>(9,9)),velocity(0.02)
{
                 leftPressed = false;
                 rightPressed = false;
                 upPressed = false;
                 downPressed = false;
                map.setRefSize(512);;
}

void World::onInit()
{
    WorldLoader(1);

    getContext().textures.load(0, "qrc:/../media/Textures/meme.png");
    getContext().textures.get(0).setSmooth(true);
    getContext().textures.load(-1, "qrc:/../media/Textures/left.png");
    getContext().textures.get(-1).setSmooth(true);
    getContext().textures.load(-2, "qrc:/../media/Textures/right.png");
    getContext().textures.get(-2).setSmooth(true);
    getContext().textures.load(-3, "qrc:/../media/Textures/up.png");
    getContext().textures.get(-3).setSmooth(true);
    getContext().textures.load(-4, "qrc:/../media/Textures/down.png");
    getContext().textures.get(-4).setSmooth(true);
}

void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{
    std::complex<double> temp = mWorldLocation;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        temp +=std::complex<double>(1,0)*velocity;
        rightPressed = true;
        leftPressed = false;
        upPressed = false;
        downPressed = false;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        rightPressed = false;
        leftPressed = true;
        upPressed = false;
        downPressed = false;
        temp +=std::complex<double>(-1,0)*velocity;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        rightPressed = false;
        leftPressed = false;
        upPressed = true;
        downPressed = false;
        temp +=std::complex<double>(0,-1)*velocity;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        rightPressed = false;
        leftPressed = false;
        upPressed = false;
        downPressed = true;
        temp +=std::complex<double>(0,1)*velocity;
    }

    if(moveValid(temp)){  
        mWorldLocation = temp;   
    }

    clear();
    DrawMap(target,states);
}

void World::WorldLoader(int worldtype)
{
    worldNum = worldtype;
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
        unMoveableTerrain = {2,3,5,7,8};
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
        getContext().textures.load(8, "qrc:/../media/Textures/Tree.png");
        getContext().textures.load(9, "qrc:/../media/Textures/ShallowSaltWater.png");
        getContext().textures.load(10, "qrc:/../media/Textures/Tree.png");
        landcount = 9;
        unMoveableTerrain = {3};
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
        unMoveableTerrain = {2,4};
    }
    else {


    }
}
void World::DrawMap(sf::RenderTarget& target, sf::RenderStates states)
{
    target.clear();
    float scale = 1;
    int jumpgap = 32*scale;
    for(int x = 0;x<576*scale;x+=jumpgap)
    {
        for(int y = 0;y<576*scale;y+=jumpgap)
        {
            int type = (map.getValue(static_cast<int>(mWorldLocation.real()+x/jumpgap+0),static_cast<int>(mWorldLocation.imag()+y/jumpgap))%landcount )+1;
            mSprite.setTexture(getContext().textures.get(type));
            mSprite.setPosition(x,y);
            mSprite.setScale(scale,scale);
            target.draw(mSprite, states);
            bool atCharectorX =  characterRelativePos.real() == x/jumpgap;
            bool atCharectorY = characterRelativePos.imag() == y/jumpgap;
            if(atCharectorX&&atCharectorY)
            {
                int i = -4;
                if(leftPressed){
                    i = -1;
                }
                else if(rightPressed){
                    i = -2;
                }
                else if(upPressed){
                    i = -3;
                }
                else if(downPressed){
                    i = -4;
                }
                mCharacter.setTexture(getContext().textures.get(i));
                mCharacter.setPosition(x,y-16);
                mCharacter.setScale(scale,scale);
                mCharacter.setOrigin(0,.25);
                target.draw(mCharacter,states);



            }
        }
    }
}

std::string World::pickPlant()
{
    pickedPlants.enqueue(mWorldLocation);
    if(pickedPlants.size()>1000)
        {
            pickedPlants.dequeue();
        }
    //TODO return a plant;
    return "";
}

bool World::moveValid(std::complex<double> next)
{
    next = next + characterRelativePos;
    if(unMoveableTerrain.contains((map.getValue(static_cast<int>(next.real()),static_cast<int>(next.imag()))%landcount+1)))
    {
//        if(unMoveableTerrain.contains((map.getValue(static_cast<int>(mWorldLocation.real()),static_cast<int>(mWorldLocation.imag()))%landcount +1)))
//        {
//            return true;
//        }
        return false;
    }
    return true;
}

int World::getVelocity(){return velocity;}
void World::setVelocity(int velocity){this->velocity=velocity;}
int World::getWorldNum(){return worldNum;}
std::complex<int> World::getCharectorLocation(){return mWorldLocation;}
void World::setCharectorLocation(std::complex<int> pos){mWorldLocation=pos;}

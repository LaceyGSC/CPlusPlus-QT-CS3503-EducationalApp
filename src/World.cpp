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
    : QSFMLWidget(pos, size, context, parent),mCharacterRelativePos(std::complex<double>(9,9)),mVelocity(1)
{
                map.setRefSize(512);;
}

void World::onInit()
{
    WorldLoader(1);

    getContext().textures.load(0, "qrc:/../media/Textures/meme.png");
    getContext().textures.get(0).setSmooth(true);
}

void World::keyPressEvent(QKeyEvent* event)
{
    std::complex<double> temp = mWorldLocation;

    if(event->key() ==Qt::Key_Right){
        temp +=std::complex<double>(1,0)*mVelocity;
    }
    else if(event->key() ==Qt::Key_Left){
        temp +=std::complex<double>(-1,0)*mVelocity;
    }
    else if(event->key() ==Qt::Key_Up){
        temp +=std::complex<double>(0,-1)*mVelocity;
    }
    else if(event->key() ==Qt::Key_Down){
        temp +=std::complex<double>(0,1)*mVelocity;
    }

    if(moveValid(temp)){
        mWorldLocation = temp;
    }
}

void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{

    clear();
    DrawMap(target,states);
}

void World::WorldLoader(int worldtype)
{
    mWorldNum = worldtype;
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
        mLandCount = 12;
        mUnmoveableTerrain = {2,3,5,7,8};
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
        mLandCount = 9;
        mUnmoveableTerrain = {3};
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
        mLandCount = 11;
        mUnmoveableTerrain = {2,4};
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
            int type = (map.getValue(static_cast<int>(mWorldLocation.real()+x/jumpgap+0),static_cast<int>(mWorldLocation.imag()+y/jumpgap))%mLandCount )+1;
            mSprite.setTexture(getContext().textures.get(type));
            mSprite.setPosition(x,y);
            mSprite.setScale(scale,scale);
            target.draw(mSprite, states);
            bool atCharectorX =  mCharacterRelativePos.real() == x/jumpgap;
            bool atCharectorY = mCharacterRelativePos.imag() == y/jumpgap;
            if(atCharectorX&&atCharectorY)
            {
                mCharacter.setTexture(getContext().textures.get(0));
                mCharacter.setPosition(x,y-16);
                mCharacter.setScale(scale/2,scale/2);
                mCharacter.setOrigin(0,.25);
                target.draw(mCharacter,states);
            }
        }
    }
}

std::string World::pickPlant()
{
    mPickedPlants.enqueue(mWorldLocation);
    if(mPickedPlants.size()>1000)
        {
            mPickedPlants.dequeue();
        }
    //TODO return a plant;
    return "";
}

bool World::moveValid(std::complex<double> next)
{
    next = next + mCharacterRelativePos;
    if(mUnmoveableTerrain.contains((map.getValue(static_cast<int>(next.real()),static_cast<int>(next.imag()))%mLandCount+1)))
    {
//        if(unMoveableTerrain.contains((map.getValue(static_cast<int>(mWorldLocation.real()),static_cast<int>(mWorldLocation.imag()))%landcount +1)))
//        {
//            return true;
//        }
        return false;
    }
    return true;
}

int World::getVelocity(){return mVelocity;}
void World::setVelocity(int velocity){this->mVelocity=velocity;}
int World::getWorldNum(){return mWorldNum;}
std::complex<double> World::getCharectorLocation(){return mWorldLocation+mCharacterRelativePos;}
void World::setCharectorLocation(std::complex<double> pos){mWorldLocation=pos-mCharacterRelativePos;}

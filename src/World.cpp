/*
 * Author: King Hoe Wong, Warren Schweigert
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
#include "qdebug.h"

#include <iostream>

using namespace sf;
World::World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent),mCharacterRelativePos(std::complex<int>(9,9))
{
                map.setRefSize(512);

                sf::VideoMode temp = sf::VideoMode::getDesktopMode();
                double height = temp.height;
                mScreenScale = height/1080;
}

void World::onInit()
{
    WorldLoader(1);

    getContext().textures.load(0, "qrc:/../media/Textures/meme.png");
    getContext().textures.get(0).setSmooth(true);
}

void World::keyPressEvent(QKeyEvent* event)
{
    std::complex<int> temp = mWorldLocation;

    if(event->key() ==Qt::Key_Right){
        temp +=std::complex<int>(1,0);
    }
    else if(event->key() ==Qt::Key_Left){
        temp +=std::complex<int>(-1,0);
    }
    else if(event->key() ==Qt::Key_Up){
        temp +=std::complex<int>(0,-1);
    }
    else if(event->key() ==Qt::Key_Down){
        temp +=std::complex<int>(0,1);
    }

    if(moveValid(temp)){
        mWorldLocation = temp;
    }
}

void World::onDraw(sf::RenderTarget& target, sf::RenderStates states)
{

    clear();
    target.clear();
    int jumpgap = 32*mScreenScale;
    for(int x = 0;x<576*mScreenScale;x+=jumpgap)
    {
        for(int y = 0;y<576*mScreenScale;y+=jumpgap)
        {
            //get land type  and display it
            std::complex<int> tempLocation = mWorldLocation + std::complex<int>(x/jumpgap,y/jumpgap);
            int type = getLandValue(tempLocation);

            mSprite.setTexture(getContext().textures.get(type));
            mSprite.setPosition(x,y);
            mSprite.setScale(mScreenScale,mScreenScale);
            target.draw(mSprite, states);

            //if the main charector is here
            bool atCharectorX =  mCharacterRelativePos.real() == x/jumpgap;
            bool atCharectorY = mCharacterRelativePos.imag() == y/jumpgap;
            if(atCharectorX&&atCharectorY)
            {
                mCharacter.setTexture(getContext().textures.get(0));
                mCharacter.setPosition(x,y-16);
                mCharacter.setScale(mScreenScale/2,mScreenScale/2);
                mCharacter.setOrigin(0,.25);
                target.draw(mCharacter,states);
            }
        }
    }
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
        mUnmoveableTerrain = {3,5};
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

bool World::moveValid(std::complex<int> next)
{
    next = next + mCharacterRelativePos;
    std::complex<int> current = mWorldLocation+mCharacterRelativePos;
    if(mUnmoveableTerrain.contains(getLandValue(next)))
    {
        if(mUnmoveableTerrain.contains(getLandValue(current))) //this is so we can escape if we end up in an unmoveable block
        {
            return true;
        }
        return false;
    }
    return true;
}

int World::getLandValue(std::complex<int> pos)
{
    return map.getValue(pos.real(),pos.imag())%mLandCount+1;
}

int World::getworldNum() const
{
    return mWorldNum;
}

std::complex<int> World::getCharecterLocation() const
{
    return mWorldLocation+mCharacterRelativePos;
}

void World::setCharectorLocation(std::complex<int> pos)
{
    mWorldLocation=pos-mCharacterRelativePos;
}

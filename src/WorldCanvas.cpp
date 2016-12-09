/*
 * Author: King Hoe Wong, Warren Schweigert
 * Desc: Implementation for World class.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include "WorldCanvas.h"

#include <QResizeEvent>
#include <QSize>
#include <QQueue>
#include <QString>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Identifiers.h"
#include "ResourceManager.h"
#include "qdebug.h"
#include "Commands.h"
#include "GameState.h"

#include <iostream>

// Dimension of each tile
const sf::Vector2i WorldCanvas::TILE_DIMENSION = sf::Vector2i(32, 32);
// Number of tiles displayed (column, row)
const sf::Vector2i WorldCanvas::DISPLAY_DIMENSION = sf::Vector2i(19, 19);

WorldCanvas::WorldCanvas(const QPoint &pos, const QSize &size, State::Context context, GameState::GameContext gameContext, QWidget *parent)
    : QSFMLWidget(pos, size, context, parent)
    , mGameContext(gameContext)
    , mSprite()
    , mCharacter()
{
    //map.setRefSize(512);

    //sf::VideoMode temp = sf::VideoMode::getDesktopMode();
    //double height = temp.height;
    //mScreenScale = height/1080;

    //mCharacterDirection = Directions::ID::Up;

    setMinimumSize(TILE_DIMENSION.x * DISPLAY_DIMENSION.x, TILE_DIMENSION.y * DISPLAY_DIMENSION.y);
    setMaximumSize(TILE_DIMENSION.x * DISPLAY_DIMENSION.x, TILE_DIMENSION.y * DISPLAY_DIMENSION.y);

    //show();
    //hide();

    // Keyboard events will only respond to this class until releaseKeyboard is called
    grabKeyboard();
}

void WorldCanvas::onInit()
{
    //WorldLoader(2);
}

void WorldCanvas::onDraw(sf::RenderTarget &target, sf::RenderStates states)
{
    Level &level = mGameContext.levelManager.getCurrentLevel();

    int playerX = level.getPlayerPosition().real();
    int playerY = level.getPlayerPosition().imag();

    // Draw the terrain. Draws row by row
    for (int y = 0; y < TILE_DIMENSION.y * DISPLAY_DIMENSION.y; y += TILE_DIMENSION.y)
    {
        // Get y-coord of tile in the map from the y-coord of screen
        int tileY = (-(y / TILE_DIMENSION.y) + DISPLAY_DIMENSION.y / 2) + playerY;

        for (int x = 0; x < TILE_DIMENSION.x * DISPLAY_DIMENSION.x; x += TILE_DIMENSION.x)
        {
            // Get x-coord of tile in the map from the x-coord of screen
            int tileX = (x / TILE_DIMENSION.x - DISPLAY_DIMENSION.x / 2) + playerX;

            mSprite.setTexture(getContext().textures.get(getTerrainType(std::complex<int>(tileX, tileY))));
            mSprite.setPosition(x, y);
            target.draw(mSprite, states);
        }
    }

    // Draw the plants
    for (int y = 0; y < TILE_DIMENSION.y * DISPLAY_DIMENSION.y; y += TILE_DIMENSION.y)
    {
        // Get y-coord of tile in the map from the y-coord of screen
        int tileY = (-(y / TILE_DIMENSION.y) + DISPLAY_DIMENSION.y / 2) + playerY;

        for (int x = 0; x < TILE_DIMENSION.x * DISPLAY_DIMENSION.x; x += TILE_DIMENSION.x)
        {
            // Get x-coord of tile in the map from the x-coord of screen
            int tileX = (x / TILE_DIMENSION.x - DISPLAY_DIMENSION.x / 2) + playerX;

            if (hasPlant(std::complex<int>(tileX, tileY)))
            {
                mSprite.setTexture(getContext().textures.get(getPlantType(std::complex<int>(tileX, tileY))));
                mSprite.setPosition(x, y);
                target.draw(mSprite, states);
            }
        }
    }

    // Draw the player
    setCharacterTexture(mGameContext.player.getFacing());

    // Player is always at the center of the screen
    int screenX = (DISPLAY_DIMENSION.x / 2) * TILE_DIMENSION.x;
    int screenY = (DISPLAY_DIMENSION.y / 2) * TILE_DIMENSION.y;

    mCharacter.setPosition(screenX, screenY);
    target.draw(mCharacter, states);

    /*clear();
    target.clear();
    int jumpgap = 32;
    for(double x = 0;x<576;x+=jumpgap)
    {
        for(double y = 0;y<576;y+=jumpgap)
        {
            //get land type  and display it
            std::complex<int> tempLocation = mWorldLocation + std::complex<int>(x/jumpgap,y/jumpgap);
            int type = getLandValue(tempLocation);

            mSprite.setTexture(mLandTextures[type]);
            mSprite.setPosition(x,y);
            //mSprite.setScale(mScreenScale,mScreenScale);
            target.draw(mSprite, states);

            //if the main charector is here
            bool atCharectorX =  mCharacterRelativePos.real() == x/jumpgap;
            bool atCharectorY = mCharacterRelativePos.imag() == y/jumpgap;
            if(atCharectorX&&atCharectorY)
            {
                mCharacter.setTexture(getContext().textures.get(Tiles::ID::Bridge));
                mCharacter.setPosition(x,y-16);
                //mCharacter.setScale(mScreenScale,mScreenScale);
                mCharacter.setOrigin(0,.25);
                target.draw(mCharacter,states);
            }

            if(plantAtSpot(tempLocation))
            {
                mCharacter.setTexture(getContext().textures.get(Tiles::ID::Catnip));
                mCharacter.setPosition(x,y-16);
                //mCharacter.setScale(mScreenScale/2,mScreenScale/2);
                mCharacter.setOrigin(0,.25);
                target.draw(mCharacter,states);
            }
        }
    }*/
}

void WorldCanvas::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Right:
        movePlayer(std::complex<int>(1, 0), Directions::ID::Right);
        break;
    case Qt::Key_Left:
        movePlayer(std::complex<int>(-1, 0), Directions::ID::Left);
        break;
    case Qt::Key_Up:
        movePlayer(std::complex<int>(0, 1), Directions::ID::Up);
        break;
    case Qt::Key_Down:
        movePlayer(std::complex<int>(0, -1), Directions::ID::Down);
        break;
    }
}

void WorldCanvas::setCharacterTexture(Directions::ID facing)
{
    TextureManager &textures = getContext().textures;

    switch (facing)
    {
    case Directions::ID::Up:
        mCharacter.setTexture(textures.get(Tiles::ID::FaceUp));
        break;
    case Directions::ID::Down:
        mCharacter.setTexture(textures.get(Tiles::ID::FaceDown));
        break;
    case Directions::ID::Right:
        mCharacter.setTexture(textures.get(Tiles::ID::FaceRight));
        break;
    case Directions::ID::Left:
        mCharacter.setTexture(textures.get(Tiles::ID::FaceLeft));
        break;
    }
}

Tiles::ID WorldCanvas::getTerrainType(const std::complex<int> &position) const
{
    Level &level = mGameContext.levelManager.getCurrentLevel();

    // This should never go out of bounds
    return level.getTerrainTypes().at(level.getMap().getValue(position.real(), position.imag()) %
                                      level.getTerrainTypes().size());
}

Tiles::ID WorldCanvas::getPlantType(const std::complex<int> &position) const
{
    Level &level = mGameContext.levelManager.getCurrentLevel();

    // This should never go out of bounds
    return level.getPlantTypes().at(level.getMap().getValue(position.real(), position.imag()) %
                                    level.getPlantTypes().size());
}

unsigned int WorldCanvas::complexHash(const std::complex<int> &input) const
{

    std::hash<double> k{};
    std::complex<double> temp = std::pow(std::complex<double>(input.real(),input.imag()),2.3);

    return k(temp.real())+k(temp.imag())+k(std::abs(temp)) + k(std::arg(temp));
}

bool WorldCanvas::isMoveValid(const std::complex<int> &next) const
{
    TileManager &tileData = mGameContext.tileManager;

    return (tileData.getTileProperties(getTerrainType(next)) & Properties::ID::Walkable);
}

bool WorldCanvas::hasPlant(const std::complex<int> &position) const
{
    Level &level = mGameContext.levelManager.getCurrentLevel();
    TileManager &tileData = mGameContext.tileManager;

    unsigned int temp = complexHash(position);

    if(0 == temp % 10)
        if(!level.isPlantPicked(position) &&
           tileData.getTileProperties(getTerrainType(position)) & Properties::ID::Plantable &&
           position != std::complex<int>(0, 0))
            return true;

    return false;
}

void WorldCanvas::movePlayer(const std::complex<int> &movement, Directions::ID direction)
{
    Player &player = mGameContext.player;
    Level &level = mGameContext.levelManager.getCurrentLevel();
    GameState::Settings &settings = mGameContext.settings;

    std::complex<int> nextPosition = level.getPlayerPosition() + movement;

    // If fast turned is off, the player will face the direction if it is a different direction
    // than the current player facing
    if (settings.fastTurn)
    {
        if (isMoveValid(nextPosition))
        {
            // Pick the plant if there is one
            if (hasPlant(nextPosition))
            {
                level.addPickedPlant(nextPosition);
                level.update(&*std::unique_ptr<PickUp>(new PickUp(getPlantType(nextPosition), 1)));
            }
            level.movePlayer(movement);
            level.update(&*std::unique_ptr<Move>(new Move(direction, 1)));
        }
    }
    else
    {
        if (player.getFacing() == direction)
        {
            if (isMoveValid(nextPosition))
            {
                // Pick the plant if there is one
                if (hasPlant(nextPosition))
                {
                    level.addPickedPlant(nextPosition);
                    level.update(&*std::unique_ptr<PickUp>(new PickUp(getPlantType(nextPosition), 1)));
                }
                level.movePlayer(movement);
                level.update(&*std::unique_ptr<Move>(new Move(direction, 1)));
            }
        }
    }

    player.turn(direction);
}

//void WorldCanvas::setCharacterLocation(std::complex<int> pos)
//{
//    mWorldLocation=pos-mCharacterRelativePos;
//}

//int WorldCanvas::getworldNum() const
//{
//    return mWorldNum;
//}

//std::complex<int> WorldCanvas::getCharacterLocation() const
//{
//    return mWorldLocation+mCharacterRelativePos;
//}
//void WorldCanvas::WorldLoader(int worldtype)
//{
//    mWorldNum = worldtype;
//    if(worldtype==0)
//    {
//        //*
//        mCurrentLandNameIndex = { Tiles::ID::Bridge , Tiles::ID::DeepFreshWater , Tiles::ID::DeepSaltWater , Tiles::ID::Dirt , Tiles::ID::Fire , Tiles::ID::Grass , Tiles::ID::Mountain , Tiles::ID::QuickSand , Tiles::ID::RedSand ,
//                                  Tiles::ID::Sand , Tiles::ID::ShallowFreshWater ,  Tiles::ID::ShallowSaltWater , Tiles::ID::Tree };
//        map.setJuliaValue(std::complex<double>(-.621,0));
//        mUnmoveableTerrain = {1,2,4,6,7};
//    }
//    else if(worldtype==1)
//    {
//        map.setJuliaValue(std::complex<double>(-.5,.002));
//        mCurrentLandNameIndex = { Tiles::ID::Dirt , Tiles::ID::Grass , Tiles::ID::Mountain , Tiles::ID::Grass , Tiles::ID::Mountain , Tiles::ID::Sand , Tiles::ID::ShallowFreshWater , Tiles::ID::Tree , Tiles::ID::ShallowSaltWater , Tiles::ID::Tree };
//        mUnmoveableTerrain = {2,4};
//    }
//    else if(worldtype==2){
//        map.setJuliaValue(std::complex<double>(-.5,-.002));
//        mCurrentLandNameIndex = { Tiles::ID::Dirt , Tiles::ID::Grass , Tiles::ID::Dirt , Tiles::ID::Mountain , Tiles::ID::QuickSand , Tiles::ID::RedSand , Tiles::ID::Sand , Tiles::ID::QuickSand , Tiles::ID::RedSand , Tiles::ID::Sand , Tiles::ID::ShallowFreshWater , Tiles::ID::Tree };
//        mUnmoveableTerrain = {4,7};
//    }
//    else {



//    }

//    mLandTextures.clear();
//    for(int i = 0; i < mCurrentLandNameIndex.size();i++)
//    {
//        mLandTextures.push_back(getContext().textures.get(mCurrentLandNameIndex[i]));
//    }
//    mLandCount = mCurrentLandNameIndex.size();
//}

//Tiles::ID WorldCanvas::plantPicked()
//{
//    mPickedPlants.enqueue(mWorldLocation+mCharacterRelativePos);
//    if(mPickedPlants.size()>1000)
//    {
//        mPickedPlants.dequeue();
//    }

//    mGameContext.levelManager.getCurrentLevel().update(&*std::unique_ptr<Command>(new PickUp(Tiles::ID::Lavender, 1)));

//    return mCurrentLandNameIndex[getLandValue(mWorldLocation+mCharacterRelativePos)];
//}

//int WorldCanvas::getLandValue(std::complex<int> pos)
//{
//    return map.getValue(pos.real(),pos.imag())%mLandCount;
//}

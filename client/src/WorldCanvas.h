/*
 * Author: King Hoe Wong, Warren Schweigert
 * Desc: Represents a World. All world data should be contained and drawn in here.
 * Courtesy of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <QQueue>

#include "QSFMLWidget.h"
#include "FractalExpressionEvaluator.h"
#include "GameState.h"

#include <unordered_set>

class WorldCanvas : public QSFMLWidget
{
public :
    explicit        WorldCanvas(const QPoint &pos, const QSize &size, State::Context context, GameState::GameContext gameContext, Satchel *satchel, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget &target, sf::RenderStates states);
    virtual void    keyPressEvent(QKeyEvent *event);

//    //changes which stage you are on
//    void WorldLoader(int);
//    int getworldNum() const;

//    //location on the map
//    std::complex<int> getCharacterLocation() const;
//    void setCharacterLocation(std::complex<int>);

private:
    void setCharacterTexture(Directions::ID facing);
    Tiles::ID getTerrainType(const std::complex<int> &position) const;
    Tiles::ID getPlantType(const std::complex<int> &position) const;

    //low quality hashe for complex integers
    unsigned int complexHash(const std::complex<int> &input) const;

    //returns the validity of a move
    bool isMoveValid(const std::complex<int> &next) const;

    //returns wether a location has a plant
    bool hasPlant(const std::complex<int> &position) const;

    void movePlayer(const std::complex<int> &movement, Directions::ID direction);

private:
    // Dimension of each tile
    static const sf::Vector2i TILE_DIMENSION;
    // Number of tiles displayed (column, row)
    static const sf::Vector2i DISPLAY_DIMENSION;

    GameState::GameContext mGameContext;

    Satchel* mSatchel;

    //drawingData
    sf::Sprite  mSprite;
    sf::Sprite  mCharacter;



//    //gets an int for a land type from the map
//    int getLandValue(std::complex<int>);

//    //std::unordered_set<std::complex<int>> mPickedPlants;

//    //drawingData


//    //directional and locational data
//    std::complex<int> mWorldLocation;
//    std::complex<int> mCharacterRelativePos;


//    //q containers chosen for their contains method.
//    QList<int> mUnmoveableTerrain; //terrain types that cannot be moved on


//    std::vector<Tiles::ID> mCurrentLandNameIndex;
//    std::vector<sf::Texture> mLandTextures;

//    //used for calculating the map
//    FractalExpressionEvaluator map;

//    //which world we are in
//    int mWorldNum;

//    //how many land in the world
//    int mLandCount;

//    Tiles::ID mCharacterDirection;

    double mScreenScale = 1;

//public :
//signals:
//    Tiles::ID plantPicked();
};

#endif // WORLD_H

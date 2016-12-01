/*
 * Author: King Hoe Wong
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
#include "State.h"

class World : public QSFMLWidget
{
public :
    explicit        World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);
    virtual void keyPressEvent(QKeyEvent* event);


    std::string pickPlant();
    void WorldLoader(int);


    int getVelocity();
    void setVelocity(int);
    int getWorldNum();
    std::complex<double> getCharectorLocation();
    void setCharectorLocation(std::complex<double>);

private:

    bool moveValid(std::complex<double> next);

    sf::Sprite  mSprite;
    sf::Sprite  mCharacter;

    std::complex<double>    mWorldLocation;
    std::complex<double> mCharacterRelativePos;

    QList<int> mUnmoveableTerrain;
    QQueue<std::complex<int>> mPickedPlants;

    FractalExpressionEvaluator map;

    int mWorldNum;
    int mLandCount;
    double mVelocity;

    std::vector<sf::Texture> mLandTextures;
    std::vector<sf::Texture> mCharecterTextures;
    std::vector<sf::Texture> mPlantTextures;

};

#endif // WORLD_H

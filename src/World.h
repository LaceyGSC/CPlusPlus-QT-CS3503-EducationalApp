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
#include "FractalExspressionEvaluator.h"
#include "State.h"

class World : public QSFMLWidget
{
public :
    explicit        World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);


    std::string pickPlant();
    void WorldLoader(int);

    int getVelocity();
    void setVelocity(int);
    int getWorldNum();
    std::complex<int> getCharectorLocation();
    void setCharectorLocation(std::complex<int>);

private:
    sf::Sprite      mSprite;
    sf::Sprite      mCharacter;
    bool leftPressed;
      bool rightPressed;
        bool upPressed;
          bool downPressed;
    std::complex<double>    mWorldLocation;
    std::complex<double> characterRelativePos;
    FractalExspressionEvaluator map;

    int worldNum;
    int landcount;
    double velocity;

    QList<int> unMoveableTerrain;
    QQueue<std::complex<int>> pickedPlants;

    void DrawMap(sf::RenderTarget& target, sf::RenderStates states);
    bool moveValid(std::complex<double> next);


};

#endif // WORLD_H

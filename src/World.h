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
#include "State.h"
#include "land.h"

class World : public QSFMLWidget
{
public :
    explicit        World(const QPoint &pos, const QSize &size, State::Context &context, QWidget *parent = 0);

    virtual void    onInit();
    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);
    virtual void keyPressEvent(QKeyEvent* event);

    //changes which stage you are on
    void WorldLoader(int);
    int getworldNum() const;

    //location on the map
    std::complex<int> getCharecterLocation() const;
    void setCharectorLocation(std::complex<int>);

private:

    bool moveValid(std::complex<int> next);

    sf::Sprite  mSprite;
    sf::Sprite  mCharacter;

    std::complex<int> mWorldLocation;
    std::complex<int> mCharacterRelativePos;

    //q containers chosen for their contains method.
    QList<int> mUnmoveableTerrain; //terrain types that cannot be moved on
    QQueue<std::complex<int>> mPickedPlants;

    std::vector<QString> mCurrentLandNameIndex;
    std::vector<sf::Texture> mLandTextures;

    FractalExpressionEvaluator map;

    int getLandValue(std::complex<int>);
    unsigned int complexHash(std::complex<int>);
    bool plantAtSpot(std::complex<int>);

    int mWorldNum;
    int mLandCount;

    double mScreenScale = 1;

public :
signals:
    QString plantPicked();
};

#endif // WORLD_H

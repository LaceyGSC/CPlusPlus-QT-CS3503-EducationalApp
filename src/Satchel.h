#ifndef SATCHEL_H
#define SATCHEL_H

#include <Box2D/Box2D.h>
#include <QMouseEvent>

#include "QSFMLWidget.h"
#include "GameState.h"

class Satchel : public QSFMLWidget
{
public:
    struct ItemData
    {
        ItemData(Tiles::ID id);

        Tiles::ID id;
    };

public:
    Satchel(State::Context context, GameState::GameContext gameContext, QWidget *parent = 0);

    virtual void onInit();
    virtual void onDraw(sf::RenderTarget &target, sf::RenderStates states);

    // Spawns an item into the backpack
    void spawnItem(Tiles::ID id);

private:
    // stimulate the world
    void worldStep(b2World* world, b2Body* body);

    // create the plants that will fall into backpack
    void CreateBox(b2World& world, int mouseX, int mouseY, Tiles::ID tile); // Spawns a box at MouseX, MouseY

    // create the backpack boundary boxes
    void CreateGround(b2World& world, float x, float y);
//    void CreateLeftWall(b2World& world, float x, float y);
//    void CreateRightWall(b2World& world, float x, float y);
//    void CreateTopWall(b2World& world, float x, float y);

private:
    GameState::GameContext mGameContext;

    sf::Sprite mSprite;
    sf::Sprite mObject;

    b2World mBox2DWorld;

    std::vector<b2Body*> mRemovalBin;

//    int xPos, yPos;
//    static const float SCALE;
};

#endif // SATCHEL_H

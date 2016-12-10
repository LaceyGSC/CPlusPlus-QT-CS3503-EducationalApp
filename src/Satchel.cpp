#include "Satchel.h"

#include <cstdlib>
#include <ctime>

#include <QDebug>

//const float Satchel::SCALE = 30.f;

Satchel::ItemData::ItemData(Tiles::ID id)
    : id(id)
{
}

Satchel::Satchel(State::Context context, GameState::GameContext gameContext, QWidget *parent)
    : QSFMLWidget(QPoint(0, 0), QSize(400, 400), context, parent)
    , mGameContext(gameContext)
    , mSprite()
    , mObject()
    // Set world gravity
    , mBox2DWorld(b2Vec2(0.f, 9.8f))
    , mRemovalBin()
{
    /* initialize random seed: */
    std::srand(std::time(NULL));

    // Set canvas size
    setMinimumSize(400, 400);
    setMaximumSize(400, 400);
}

void Satchel::onInit()
{
    /** Prepare the world */
    // Only need this
    CreateGround(mBox2DWorld, 420.f, 500.f);  // stretches in right direction, stretches vertically
    //CreateLeftWall(mBox2DWorld, -250.f, 100.f); // create ground
    //CreateRightWall(mBox2DWorld, 1000.f, 100.f);
    //CreateTopWall(mBox2DWorld, 400.f, 1000.f);

    /** load images for backpack and plant */
//    getContext().textures.load(Tiles::ID::SatchelTop, "qrc:/../media/Textures/satcheltop.png");
//    getContext().textures.load(Tiles::ID::SatchelRight, "qrc:/../media/Textures/satchelright.png");
//    getContext().textures.load(Tiles::ID::SatchelLeft, "qrc:/../media/Textures/satchelleft.png");
//    getContext().textures.load(Tiles::ID::SatchelBottom, "qrc:/../media/Textures/satchelbottom.png");

    // Moved texture loading to Application.cpp. Textures should only be loaded once
}

void Satchel::onDraw(sf::RenderTarget &target, sf::RenderStates states)
{
    // Reset the canvas with the default Qt background color
    auto bgColor = palette().color(backgroundRole());
    target.clear(sf::Color(bgColor.red(), bgColor.green(), bgColor.blue(), bgColor.alpha()));


    // Draw the satchel first so that it appears as the background
    // Make the satchel fit the canvas
    auto textureSize = getContext().textures.get(Tiles::ID::Satchel).getSize();
    float scaleX = (float)width() / textureSize.x;
    float scaleY = (float)height() / textureSize.y;
    mSprite.setTexture(getContext().textures.get(Tiles::ID::Satchel));
    mSprite.setOrigin(0.f, 0.f);
    mSprite.setPosition(0, 0);
    mSprite.setScale(scaleX, scaleY);

    target.draw(mSprite, states);

    mBox2DWorld.Step(1/15.f, 8, 3);


    // Draw the items falling into the backpack
    for (b2Body* BodyIterator = mBox2DWorld.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        /** draw the plants */
        if (BodyIterator->GetType() == b2_dynamicBody)
        {
            // Mark bodies that are out of the screen for removal
            if (BodyIterator->GetPosition().y > 400)
                mRemovalBin.push_back(BodyIterator);

            auto data = static_cast<ItemData*>(BodyIterator->GetUserData());

            mObject.setTexture(getContext().textures.get(data->id));
            mObject.setOrigin(16.f, 16.f);
            mObject.setScale(1.f, 1.f);
            mObject.setPosition(BodyIterator->GetPosition().x, BodyIterator->GetPosition().y);
            mObject.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
            target.draw(mObject, states);
        }
    }

    // Remove the marked bodies after the iteration to prevent crash from changing the
    // container size halfway through the iteration
    for (auto &it : mRemovalBin)
    {
        delete it->GetUserData();
        mBox2DWorld.DestroyBody(it);
    }

    // Reset marking container
    mRemovalBin.clear();


//    /** put images onto window */
//    for (b2Body* BodyIterator = mBox2DWorld.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
//    {
//        /** draw the plants */
//        if (BodyIterator->GetType() == b2_dynamicBody)
//        {
//            mSprite.setTexture(getContext().textures.get(Tiles::ID::Catnip));

//            mSprite.setOrigin(16.f, 16.f);
//            mSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
//            mSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
//            target.draw(mSprite, states);
//        }
//    }

//    // make satchel right side
//    mSprite.setTexture(getContext().textures.get(Tiles::ID::SatchelRight));
//    mSprite.setPosition(width() * .875, height() * -.25);
//    target.draw(mSprite, states);

//    // make satchel left side
//    mSprite.setTexture(getContext().textures.get(Tiles::ID::SatchelLeft));
//    mSprite.setPosition(width() * .05, height() * -.25);
//    target.draw(mSprite, states);

//    // make satchel bottom side
//    mSprite.setTexture(getContext().textures.get(Tiles::ID::SatchelBottom));
//    mSprite.setPosition(width() * .055, height() * .81);
//    target.draw(mSprite, states);

//    // make satchel top side
//    mSprite.setTexture(getContext().textures.get(Tiles::ID::SatchelTop));
//    mSprite.setPosition(250, 0);
//    target.draw(mSprite, states);
}

void Satchel::spawnItem(Tiles::ID id)
{
    /* generate random number between 90 and 390: */
    int x = std::rand() % 300 + 90;

    CreateBox(mBox2DWorld, x, 10, id);
}


/************************************************** METHODS TO CREATE THE BOX2D FOR THE BACKPACK BOUNDARIES*****************************/

/************************************************** REFRACTOR LATER*****************************/

void Satchel::CreateBox(b2World& world, int mouseX, int mouseY, Tiles::ID tile)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(mouseX, mouseY);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = world.CreateBody(&BodyDef);

    // Make the item circle so it rolls easily
    b2CircleShape Shape;
    Shape.m_radius = 16.f;
    b2FixtureDef FixtureDef;
    FixtureDef.density = 200.f;
    FixtureDef.friction = 0.7f;
    // Gives bounciness
    FixtureDef.restitution = 0.2f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData(new ItemData(tile));
}

void Satchel::CreateGround(b2World& world, float x, float y)
{
    // create body definition
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(0.0f, 60.0f);
    bodyDef.type = b2_staticBody;

    // create body by giving world body definition
    b2Body* body = world.CreateBody(&bodyDef);

    b2EdgeShape edge;

    // bottom
    edge.Set(b2Vec2(85, 330), b2Vec2(395, 330));
    body->CreateFixture(&edge, 1.0f);

    // left
    edge.Set(b2Vec2(85, 0), b2Vec2(85, 340));
    body->CreateFixture(&edge, 1.0f);

    // right
    edge.Set(b2Vec2(395, 0), b2Vec2(395, 340));
    body->CreateFixture(&edge, 1.0f);

//    shape.SetAsBox(0.5f, 10.0f, b2Vec2( 10.0f, 0.0f), 0.0);
//    body->CreateFixture(&edge, 5.0f);
//    shape.SetAsBox(0.5f, 10.0f, b2Vec2(-10.0f, 0.0f), 0.0);
//    body->CreateFixture(&edge, 5.0f);
//    shape.SetAsBox(10.0f, 0.5f, b2Vec2(0.0f, 10.0f), 0.0);
//    body->CreateFixture(&edge, 5.0f);
//    shape.SetAsBox(10.0f, 0.5f, b2Vec2(0.0f, -10.0f), 0.0);
}

//void Satchel::CreateLeftWall(b2World& world, float x, float y)
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(x/SCALE, y/SCALE);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = world.CreateBody(&BodyDef);

//    b2PolygonShape Shape;
//    Shape.SetAsBox(500.f/SCALE, 800.f/SCALE);

//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body ->CreateFixture(&FixtureDef);
//}

//void Satchel::CreateRightWall(b2World& world, float x, float y)
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(x/SCALE, y/SCALE);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = world.CreateBody(&BodyDef);

//    b2PolygonShape Shape;


//    Shape.SetAsBox(160.f/SCALE, 800.f/SCALE);

//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body ->CreateFixture(&FixtureDef);
//}

//void Satchel::CreateTopWall(b2World& world, float x, float y)
//{
//    b2BodyDef BodyDef;
//    //BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
//    BodyDef.position = b2Vec2(13, 18);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = world.CreateBody(&BodyDef);

//    b2PolygonShape Shape;


//    Shape.SetAsBox(440.f/SCALE, -800.f/SCALE);

//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body ->CreateFixture(&FixtureDef);
//}



//void Satchel::worldStep(b2World* world, b2Body* body)
//{
//    float32 timeStep = 1.0f / 1000.0f;

//    int32 velocityIterations = 6;
//    int32 positionIterations = 2;

//    world->Step(timeStep, velocityIterations, positionIterations);
//    b2Vec2 position = body->GetPosition();

//    xPos = position.x;
//    yPos = position.y;
//}

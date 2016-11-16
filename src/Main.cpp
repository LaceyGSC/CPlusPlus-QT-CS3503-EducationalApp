#include <QApplication>
#include <QFrame>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    QFrame* mainFrame = new QFrame;
    mainFrame->setWindowTitle("Edu App");
    mainFrame->resize(400, 400);
    mainFrame->show();

    sf::RenderWindow window();

    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(100.f, 100.f);
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox((32.f/2)/3, (32.f/2)/3);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    return App.exec();
}

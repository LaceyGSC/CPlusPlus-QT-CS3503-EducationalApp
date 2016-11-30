#ifndef CHARACTER_H
#define CHARACTER_H


#include <SFML/Graphics.hpp>

#include "QSFMLWidget.h"
#include "State.h"

class Character : public QSFMLWidget
{
public :
//    explicit        Character(const QPoint &pos, const QSize &size, State::Context context, QWidget *parent = 0);

//    virtual void    onInit();
//    virtual void    onDraw(sf::RenderTarget& target, sf::RenderStates states);

private:
    sf::Sprite      mSprite;
};

#endif // CHARACTER_H

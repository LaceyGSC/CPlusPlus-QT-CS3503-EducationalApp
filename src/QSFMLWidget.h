/*
 * Author: King Hoe Wong
 * Desc: Abstract class for a Qt + SFML widget. This widget will allow SFML to draw onto the widget
 *       to display the sprites.
 * Courtest of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#ifndef QSFMLWidget_H
#define QSFMLWidget_H

#include <QWidget>
#include <QTimer>

#include <SFML/Graphics.hpp>

class QSFMLWidget : public QWidget, public sf::RenderWindow
{
public:
    // The default value of 0 for refreshTime will make the timer trigger a refresh whenever
    // there is no other event to process and we want the widget to refresh as many times
    // as possible for a smooth display
    explicit QSFMLWidget(const QPoint &pos, const QSize &size, QWidget *parent = 0, unsigned int refreshTime = 0);
    virtual ~QSFMLWidget();

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);

    virtual void onInit() = 0;
    virtual void onUpdate() = 0;

private:
    QTimer mRefreshTimer;
    bool mInitialized;
};

#endif // QSFMLWidget_H

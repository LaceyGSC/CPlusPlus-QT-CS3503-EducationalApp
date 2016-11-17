/*
 * Author: King Hoe Wong
 * Desc: Program entry.
 * Courtest of: http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html
 *
 */

#include <QApplication>
#include <QFrame>

#include "SFMLCanvas.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    // Create the main frame
    QFrame* mainFrame = new QFrame;
    mainFrame->setWindowTitle("Edu App");
    mainFrame->resize(800, 600);
    mainFrame->show();

    // Create a SFML view inside the main frame
    SFMLCanvas* SFMLView = new SFMLCanvas(QPoint(100, 100), QSize(600, 400), mainFrame);
    SFMLView->show();
    return App.exec();
}

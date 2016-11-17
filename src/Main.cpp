/*
 * Author: King Hoe Wong
 * Desc: Program entry.
 *
 */

#include <QApplication>
#include <QFrame>

#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    Application mainWindow;
    mainWindow.show();

    return App.exec();
}

/*
 * Author: King Hoe Wong
 * Desc: Program entry.
 *
 */

#include <QApplication>
#include <QFrame>

#include "Application.h"

#include <exception>
#include <iostream>

int main(int argc, char *argv[]) try
{
    QApplication App(argc, argv);

    Application mainWindow;
    mainWindow.show();

    return App.exec();
}
catch(std::exception &e)
{
    std::cerr << e.what() << std::endl;
}
catch(...)
{
    std::cerr << "Unknown exception caught." << std::endl;
}

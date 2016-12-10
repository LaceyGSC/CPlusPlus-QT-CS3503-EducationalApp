#ifndef ADMINSTATE_H
#define ADMINSTATE_H

#include <QWidget>

#include "State.h"
#include "StateStack.h"
#include "ServerConnection.h"
#include "Character.h"
#include <vector>
#include <QTableWidget>

namespace Ui {
class AdminState;
}

class AdminState : public State
{
    Q_OBJECT

public:
    explicit AdminState(StateStack &stack, Context &context, QWidget *parent = 0);
    ~AdminState();

    virtual bool        update(const sf::Time &deltaTime);

private:
    Ui::AdminState *ui;
    ServerConnection connection;
    int masterNum = 0;

    std::vector<Character> characterVect;

    void createArray();
    void createListView();

private slots:
    void deleteSlot();
    void viewSlot();
    void logSlot();
    void selectedSlot(int, int);

};

#endif // ADMINSTATE_H

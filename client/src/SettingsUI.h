#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <QWidget>

#include <memory>

#include "GameState.h"

namespace Ui {
class SettingsUI;
}

class SettingsUI : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsUI(GameState::GameContext context, QWidget *parent = 0);
    ~SettingsUI();

private slots:
    void toggleFastTurn(bool toggle);

private:
    Ui::SettingsUI *mUi;

    GameState::GameContext mGameContext;
};

#endif // SETTINGSUI_H

#ifndef LOGINSTATE_H
#define LOGINSTATE_H

#include <QWidget>

namespace Ui {
class LoginState;
}

class LoginState : public QWidget
{
    Q_OBJECT

public:
    explicit LoginState(QWidget *parent = 0);
    ~LoginState();

private:
    Ui::LoginState *ui;
};

#endif // LOGINSTATE_H

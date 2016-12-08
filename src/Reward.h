#ifndef REWARD_H
#define REWARD_H

#include <QWidget>
#include <QString>

#include <functional>

namespace Ui {
class Reward;
}

class Reward : public QWidget
{
    Q_OBJECT

public:
    explicit Reward(const QString& desc, QWidget *parent = 0);
    ~Reward();

    void setOnActivate(const std::function<void()>& callback);
    void setOnDeactivate(const std::function<void()>& callback);

    void activate();
    void deactivate();

private:
    Ui::Reward *mUi;

    std::function<void()> mActivateCallback;
    std::function<void()> mDeactivateCallback;

    bool mReaped;
};

#endif // REWARD_H

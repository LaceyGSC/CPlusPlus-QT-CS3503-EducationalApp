#ifndef PLANTODEX_H
#define PLANTODEX_H

#include <QWidget>

namespace Ui {
class Plantodex;
}

class Plantodex : public QWidget
{
    Q_OBJECT

public:
    explicit Plantodex(QWidget *parent = 0);
    ~Plantodex();

private:
    Ui::Plantodex *ui;
};

#endif // PLANTODEX_H

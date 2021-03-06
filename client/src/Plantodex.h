// Author: Mat Mason
// Description: Implementation of Plantodex Class. Model for Plantodex Gui.

#ifndef PLANTODEX_H
#define PLANTODEX_H

#include <QWidget>
#include <vector>
#include <QtGui>
#include <SFML/Graphics.hpp>
#include "Application.h"

namespace Ui {
class Plantodex;
}

class Plantodex : public QWidget
{
    Q_OBJECT

private slots:
    void on_plantListView_clicked(const QModelIndex &index);

public:
    explicit Plantodex(QWidget *parent = 0);
    ~Plantodex();

    void setUpPlantodex(QString *string);

private:
    Ui::Plantodex *ui;
    std::vector<QString> book;
    QStringListModel *list = new QStringListModel();
    QString plantNames;
    sf::Image image;

    void getPlantNames(std::vector<QString> book);
    void updatePlantodex(int index);
};

#endif // PLANTODEX_H

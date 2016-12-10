#ifndef QUICKPLANTANALYZER_H
#define QUICKPLANTANALYZER_H

#include <QWidget>

namespace Ui {
class QuickPlantAnalyzer;
}

class QuickPlantAnalyzer : public QWidget
{
    Q_OBJECT

public:
    explicit QuickPlantAnalyzer(QWidget *parent = 0);
    ~QuickPlantAnalyzer();

private:
    Ui::QuickPlantAnalyzer *mUi;
};

#endif // QUICKPLANTANALYZER_H

#include "Quest.h"
#include "ui_Quest.h"

#include "Level.h"

Quest::Quest(const QString &title, const QString &description, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::Quest)
{
    mUi->setupUi(this);

    mUi->title->setText(title);
    mUi->description->setText(description);

    show();


    /*progressBar = new QProgressBar(Quest);
    progressBar->setObjectName(QStringLiteral("progressBar"));
    progressBar->setMinimumSize(QSize(80, 21));
    progressBar->setMaximumSize(QSize(80, 21));
    progressBar->setValue(0);
    progressBar->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(progressBar, 0, 1, 1, 1);

    progressBar->setFormat(QApplication::translate("Quest", "%p%", 0));

        description = new QLabel(Quest);
        description->setObjectName(QStringLiteral("description"));
        description->setFrameShape(QFrame::Box);
        description->setFrameShadow(QFrame::Sunken);
        description->setWordWrap(true);

        gridLayout->addWidget(description, 1, 0, 1, 2);*/
}

Quest::~Quest()
{
    delete mUi;
}

void Quest::setCompletion(int val)
{
    mUi->progressBar->setValue(val);

    if (mUi->progressBar->value() >= 100)
        static_cast<Level*>(parent())->addCompletedQuest();
}

int Quest::getCompletion() const
{
    return mUi->progressBar->value();
}

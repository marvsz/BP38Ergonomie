#include "executionconditionview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QScroller>

ExecutionConditionView::ExecutionConditionView(QWidget *parent) :
    QMainWindow(parent)
{
    btnMoreExecutionCondition = new SelectableValueButton(2, 2, this);
    btnMoreExecutionCondition->setText("Weitere");
    btnMoreExecutionCondition->setMinimumWidth(150);
    moreExecutionCondition = new MoreExecutionCondition(this);
    connect(btnMoreExecutionCondition, SIGNAL(clicked()), this, SLOT(moreExecutionConditionSelected()));

    btnGeneralExecutionCondition = new SelectableValueButton(0, 0, this);
    btnGeneralExecutionCondition->setText("Allgemein");
    btnGeneralExecutionCondition->setMinimumWidth(150);
    generalExecutionCondition = new GeneralExecutionCondition(this);
    connect(btnGeneralExecutionCondition, SIGNAL(clicked()), this, SLOT(generalExecutionConditionSelected()));

    scMainContent = new QScrollArea(this);
    scMainContent->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);

    lytOptions = new QVBoxLayout;
    lytOptions->addWidget(btnGeneralExecutionCondition, 0, Qt::AlignTop);
    lytOptions->addWidget(btnMoreExecutionCondition, 0, Qt::AlignTop);
    lytOptions->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    mainContentLayout = new QHBoxLayout;
    mainContentLayout->addLayout(lytOptions);
    mainContentLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    mainContentLayout->addWidget(scMainContent);
    mainContent = new QWidget();
    mainContent->setLayout(mainContentLayout);


    this->setCentralWidget(mainContent);

    currentSelectedBtn = btnMoreExecutionCondition;
    generalExecutionConditionSelected();
}

//private slots
void ExecutionConditionView::moreExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnMoreExecutionCondition->setSelected(true);
    scMainContent->setWidget(new MoreExecutionCondition(this));
    currentSelectedBtn = btnMoreExecutionCondition;
}

void ExecutionConditionView::generalExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnGeneralExecutionCondition->setSelected(true);
    scMainContent->setWidget(new GeneralExecutionCondition(this));
    currentSelectedBtn = btnGeneralExecutionCondition;
}

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
    connect(btnMoreExecutionCondition, SIGNAL(clicked()), this, SLOT(moreExecutionConditionSelected()));

    btnGeneralExecutionCondition = new SelectableValueButton(0, 0, this);
    btnGeneralExecutionCondition->setText("Allgemein");
    btnGeneralExecutionCondition->setMinimumWidth(150);
    connect(btnGeneralExecutionCondition, SIGNAL(clicked()), this, SLOT(generalExecutionConditionSelected()));

    QWidget *executionConditionContent = new QWidget(this);
    QVBoxLayout *eccLayout = new QVBoxLayout;
    generalExecutionCondition = new GeneralExecutionCondition(executionConditionContent);
    moreExecutionCondition = new MoreExecutionCondition(executionConditionContent);
    eccLayout->addWidget(generalExecutionCondition);
    eccLayout->addWidget(moreExecutionCondition);
    generalExecutionCondition->hide();
    moreExecutionCondition->hide();
    executionConditionContent->setLayout(eccLayout);

    scMainContent = new QScrollArea(this);
    scMainContent->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);
    scMainContent->setWidget(executionConditionContent);


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
    moreExecutionCondition->show();
    generalExecutionCondition->hide();
    currentSelectedBtn = btnMoreExecutionCondition;
}

void ExecutionConditionView::generalExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnGeneralExecutionCondition->setSelected(true);
    generalExecutionCondition->show();
    moreExecutionCondition->hide();
    currentSelectedBtn = btnGeneralExecutionCondition;
}

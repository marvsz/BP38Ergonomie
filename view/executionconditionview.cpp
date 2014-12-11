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

    btnUtilitiesExecutionCondition = new SelectableValueButton(1, 1, this);
    btnUtilitiesExecutionCondition->setText("Betriebsmittel");
    btnUtilitiesExecutionCondition->setMinimumWidth(150);
    utilitiesExecutionCondition = new UtilityListControl("Betriebsmittel", this);
    connect(btnUtilitiesExecutionCondition, SIGNAL(clicked()), this, SLOT(utilitiesExecutionConditionSelected()));

    btnGeneralExecutionCondition = new SelectableValueButton(0, 0, this);
    btnGeneralExecutionCondition->setText("Allgemein");
    btnGeneralExecutionCondition->setMinimumWidth(150);
    connect(btnGeneralExecutionCondition, SIGNAL(clicked()), this, SLOT(generalExecutionConditionSelected()));

    QWidget *executionConditionContent = new QWidget(this);
    QVBoxLayout *eccLayout = new QVBoxLayout;
    generalExecutionCondition = new GeneralExecutionCondition(executionConditionContent);
    utilitiesExecutionCondition = new UtilityListControl("Betriebsmittel", executionConditionContent);
    moreExecutionCondition = new MoreExecutionCondition(executionConditionContent);
    eccLayout->addWidget(generalExecutionCondition);
    eccLayout->addWidget(utilitiesExecutionCondition);
    eccLayout->addWidget(moreExecutionCondition);
    generalExecutionCondition->hide();
    utilitiesExecutionCondition->hide();
    moreExecutionCondition->hide();
    executionConditionContent->setLayout(eccLayout);

    scMainContent = new QScrollArea(this);
    scMainContent->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);
    scMainContent->setWidget(executionConditionContent);


    lytOptions = new QVBoxLayout;
    lytOptions->addWidget(btnGeneralExecutionCondition, 0, Qt::AlignTop);
    lytOptions->addWidget(btnUtilitiesExecutionCondition, 0, Qt::AlignTop);
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
    generalExecutionCondition->hide();
    utilitiesExecutionCondition->hide();
    moreExecutionCondition->show();
    currentSelectedBtn = btnMoreExecutionCondition;
}

void ExecutionConditionView::generalExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnGeneralExecutionCondition->setSelected(true);
    generalExecutionCondition->show();
    utilitiesExecutionCondition->hide();
    moreExecutionCondition->hide();
    currentSelectedBtn = btnGeneralExecutionCondition;
}

void ExecutionConditionView::utilitiesExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnUtilitiesExecutionCondition->setSelected(true);
    generalExecutionCondition->hide();
    utilitiesExecutionCondition->show();
    moreExecutionCondition->hide();
    currentSelectedBtn = btnUtilitiesExecutionCondition;
}

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
    connect(btnUtilitiesExecutionCondition, SIGNAL(clicked()), this, SLOT(utilitiesExecutionConditionSelected()));

    btnGeneralExecutionCondition = new SelectableValueButton(0, 0, this);
    btnGeneralExecutionCondition->setText("Allgemein");
    btnGeneralExecutionCondition->setMinimumWidth(150);
    connect(btnGeneralExecutionCondition, SIGNAL(clicked()), this, SLOT(generalExecutionConditionSelected()));

    btnProducedProductExecutionCondition = new SelectableValueButton(0, 0, this);
    btnProducedProductExecutionCondition->setText("Produkt");
    btnProducedProductExecutionCondition->setMinimumWidth(150);
    connect(btnProducedProductExecutionCondition, SIGNAL(pressed()), this, SLOT(producedProductExecutionConditionSelected()));

    QWidget *executionConditionContent = new QWidget(this);
    QVBoxLayout *eccLayout = new QVBoxLayout;
    generalExecutionCondition = new GeneralExecutionCondition(executionConditionContent);
    utilitiesExecutionCondition = new UtilityListControl(executionConditionContent);
    moreExecutionCondition = new MoreExecutionCondition(executionConditionContent);
    producedProductExecutionCondition = new ProducedProductExecutionCondition(executionConditionContent);
    eccLayout->addWidget(generalExecutionCondition);
    eccLayout->addWidget(producedProductExecutionCondition);
    eccLayout->addWidget(utilitiesExecutionCondition);
    eccLayout->addWidget(moreExecutionCondition);
    generalExecutionCondition->hide();
    producedProductExecutionCondition->hide();
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
    lytOptions->addWidget(btnProducedProductExecutionCondition, 0, Qt::AlignTop);
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

    currentSelectedBtn = btnGeneralExecutionCondition;
    currentShownWidget = generalExecutionCondition;
    generalExecutionConditionSelected();
}

//private slots
void ExecutionConditionView::moreExecutionConditionSelected(){
    showHide(btnMoreExecutionCondition, moreExecutionCondition);
}

void ExecutionConditionView::generalExecutionConditionSelected(){
    showHide(btnGeneralExecutionCondition, generalExecutionCondition);
}

void ExecutionConditionView::utilitiesExecutionConditionSelected(){
    showHide(btnUtilitiesExecutionCondition, utilitiesExecutionCondition);
}

void ExecutionConditionView::producedProductExecutionConditionSelected(){
    showHide(btnProducedProductExecutionCondition, producedProductExecutionCondition);
}

// private functions
void ExecutionConditionView::showHide(SelectableValueButton *btn, QWidget *content){
    currentSelectedBtn->setSelected(false);
    btn->setSelected(true);
    currentShownWidget->hide();
    content->show();
    currentSelectedBtn = btn;
    currentShownWidget = content;
}

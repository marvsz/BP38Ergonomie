#include "executionconditionview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QScroller>

ExecutionConditionView::ExecutionConditionView(QWidget *parent) :
    QMainWindow(parent)
{
    btnBack = new QPushButton(this);
    btnBack->setText("< Zurück");
    btnBack->setFixedSize(120, 45);
    connect(btnBack, SIGNAL(clicked()), this, SLOT(openMenuView()));

    lblViewName = new QLabel(this);
    lblViewName->setText("Ausführungsbedingungen");

    btnMoreExecutionCondition = new SelectableValueButton(2, 2, this);
    btnMoreExecutionCondition->setText("Weitere");
    btnMoreExecutionCondition->setMinimumWidth(200);
    moreExecutionCondition = new MoreExecutionCondition(this);
    connect(btnMoreExecutionCondition, SIGNAL(clicked()), this, SLOT(moreExecutionConditionSelected()));

    btnGeneralExecutionCondition = new SelectableValueButton(0, 0, this);
    btnGeneralExecutionCondition->setText("Allgemein");
    btnGeneralExecutionCondition->setMinimumWidth(200);
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


    mainLayout = new QGridLayout;
    mainLayout->addWidget(btnBack, 0, 0, 1, 1, 0);
    mainLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(mainContent, 1, 0, 1, 2, 0);

    main = new QWidget(this);
    main->setLayout(mainLayout);
    this->setCentralWidget(main);

    currentSelectedBtn = btnMoreExecutionCondition;
    generalExecutionConditionSelected();
}

//public slots
void ExecutionConditionView::openMenuView(){
    emit menuViewSelected();
}

//private slots
void ExecutionConditionView::moreExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnMoreExecutionCondition->setSelected(true);
    scMainContent->setWidget(moreExecutionCondition);
    currentSelectedBtn = btnMoreExecutionCondition;
}

void ExecutionConditionView::generalExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnGeneralExecutionCondition->setSelected(true);
    scMainContent->setWidget(generalExecutionCondition);
    currentSelectedBtn = btnGeneralExecutionCondition;
}

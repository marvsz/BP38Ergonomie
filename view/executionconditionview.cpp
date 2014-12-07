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
    moreExecutionCondition = new MoreExecutionCondition(this);

    scMainContent = new QScrollArea(this);
    scMainContent->setWidgetResizable(true);
    //QScroller::grabGesture(scMainContent->viewport(), QScroller::LeftMouseButtonGesture);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);

    lytOptions = new QVBoxLayout;
    lytOptions->addWidget(btnMoreExecutionCondition, 0, Qt::AlignTop);

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
    moreExecutionConditionSelected();
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

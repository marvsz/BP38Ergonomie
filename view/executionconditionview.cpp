#include "executionconditionview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QScroller>

ExecutionConditionView::ExecutionConditionView(QWidget *parent) :
    QMainWindow(parent)
{
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


    this->setCentralWidget(mainContent);

    currentSelectedBtn = btnMoreExecutionCondition;
    moreExecutionConditionSelected();
}

//private slots
void ExecutionConditionView::moreExecutionConditionSelected(){
    currentSelectedBtn->setSelected(false);
    btnMoreExecutionCondition->setSelected(true);
    scMainContent->setWidget(moreExecutionCondition);
    currentSelectedBtn = btnMoreExecutionCondition;
}

#include "workplacelistview.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "separator.h"

WorkplaceListView::WorkplaceListView(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *navigationLayout = new QGridLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    btnBack = new QPushButton("< Zurück");
    btnBack->setObjectName("btnNavigation");
    btnForward = new QPushButton("+");
    btnForward->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
    connect(btnForward, SIGNAL(clicked()), this, SLOT(forwardButtonClicked()));

    workplaceListView = new QListView();
    workplaceList = new QStringListModel();
    workplaceListView->setModel(workplaceList);

    navigationLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationLayout->addWidget(new QLabel("Arbeitsplätze"), 0, 1, 1, 1, Qt::AlignCenter);
    navigationLayout->addWidget(btnForward, 0, 2, 1, 1, Qt::AlignRight);

    mainLayout->addLayout(navigationLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(workplaceListView);

    this->setLayout(mainLayout);

    updateWorkplaces(QStringList() << "Arbeitsplatz 1" << "Arbeitsplatz 2" << "Arbeitsplatz 3");
}

void WorkplaceListView::updateWorkplaces(const QStringList &workplaces){
    workplaceList->setStringList(workplaces);
}

void WorkplaceListView::backButtonClicked(){
    emit showPreviousView();
}

void WorkplaceListView::forwardButtonClicked(){
    emit showNewWorkplaceView();
}


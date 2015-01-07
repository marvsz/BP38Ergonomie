#include "workplacelistview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include <QStringList>

WorkplaceListView::WorkplaceListView(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *navigationLayout = new QGridLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *listContentLayout = new QVBoxLayout;

    QWidget *listContent = new QWidget;

    btnBack = new QPushButton("< Zurück");
    btnBack->setObjectName("btnNavigation");
    btnForward = new QPushButton("+");
    btnForward->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
    connect(btnForward, SIGNAL(clicked()), this, SLOT(forwardButtonClicked()));

    scWorkplaces = new QScrollArea();
    scWorkplaces->setWidget(listContent);
    scWorkplaces->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scWorkplaces);

    listContentLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    navigationLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationLayout->addWidget(new QLabel("Arbeitsplätze"), 0, 1, 1, 1, Qt::AlignCenter);
    navigationLayout->addWidget(btnForward, 0, 2, 1, 1, Qt::AlignRight);

    listContent->setLayout(listContentLayout);

    mainLayout->addLayout(navigationLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scWorkplaces);

    this->setLayout(mainLayout);
}

void WorkplaceListView::updateWorkplaces(const QStringList &workplaces){

}

void WorkplaceListView::backButtonClicked(){
    emit showPreviousView();
}

void WorkplaceListView::forwardButtonClicked(){
    emit showNewWorkplaceView();
}


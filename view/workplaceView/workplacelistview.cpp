#include "workplacelistview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include <QStringList>

const QList<QStringList> WorkplaceListView::workplaceCaptions = QList<QStringList>() << (QStringList() << "Beschreibung" << "Code");

WorkplaceListView::WorkplaceListView(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *navigationLayout = new QGridLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    listContentLayout = new QVBoxLayout;

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

    navigationLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationLayout->addWidget(new QLabel("Arbeitsplätze"), 0, 1, 1, 1, Qt::AlignCenter);
    navigationLayout->addWidget(btnForward, 0, 2, 1, 1, Qt::AlignRight);

    listContent->setLayout(listContentLayout);

    mainLayout->addLayout(navigationLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scWorkplaces);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    this->setLayout(mainLayout);
}

void WorkplaceListView::clear(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void WorkplaceListView::addWorkplace(int id, const QString &name, const QString &description, const QString &code){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << description << code);
    DetailedListItem *newListItem = new DetailedListItem(this, "", name, workplaceCaptions, true);
    newListItem->setValues(values);
    newListItem->setID(id);
    listContentLayout->addWidget(newListItem);
}

void WorkplaceListView::backButtonClicked(){
    emit showPreviousView();
}

void WorkplaceListView::forwardButtonClicked(){
    emit showNewWorkplaceView();
}


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

    btnBack = new QPushButton(tr("< back"));
    btnBack->setObjectName("btnNavigation");
    btnForward = new QPushButton("+");
    btnForward->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(btnForward, SIGNAL(clicked()), this, SIGNAL(forward()));

    scWorkplaces = new QScrollArea();
    scWorkplaces->setWidget(listContent);
    scWorkplaces->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scWorkplaces);

    navigationLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationLayout->addWidget(new QLabel(tr("work stations")), 0, 1, 1, 1, Qt::AlignCenter);
    navigationLayout->addWidget(btnForward, 0, 2, 1, 1, Qt::AlignRight);

    listContent->setLayout(listContentLayout);

    mainLayout->addLayout(navigationLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scWorkplaces);

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
    connect(newListItem, SIGNAL(pressed(int)), this, SIGNAL(showWorkplace(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteWorkplace(int)));
    listContentLayout->addWidget(newListItem);
}

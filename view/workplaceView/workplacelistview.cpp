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

    // TEST
    /*
    QStringList captionsOneRowOne;
    captionsOneRowOne << "Bezeichnung";
    QStringList captionsOneRowTwo;
    captionsOneRowTwo << "Beschreibung";
    QList<QStringList> captionsOne;
    captionsOne.append(captionsOneRowOne);
    captionsOne.append(captionsOneRowTwo);

    QStringList valuesOneRowOne;
    valuesOneRowOne << "Linie 1";
    QStringList valuesOneRowTwo;
    valuesOneRowTwo << "Eine ganz tolle Linie";
    QList<QStringList> valuesOne;
    valuesOne.append(valuesOneRowOne);
    valuesOne.append(valuesOneRowTwo);

    QStringList captionsTwoRowOne;
    captionsTwoRowOne << "Schichtart" << "Stückzahl" << "Taktzeit";
    QStringList captionsTwoRowTwo;
    captionsTwoRowTwo << "Beginn" << "Ende";
    QList<QStringList> captionsTwo;
    captionsTwo.append(captionsTwoRowOne);
    captionsTwo.append(captionsTwoRowTwo);

    QStringList valuesTwoRowOne;
    valuesTwoRowOne << "Frühschicht" << "3" << "10 Minuten";
    QStringList valuesTwoRowTwo;
    valuesTwoRowTwo << "06:00" << "14:00";
    QList<QStringList> valuesTwo;
    valuesTwo.append(valuesTwoRowOne);
    valuesTwo.append(valuesTwoRowTwo);

    DetailedListItem *listItemOne = new DetailedListItem(listContent, ":/icons/specialPurposeIcons/camera.png", "Linie", captionsOne, true);
    DetailedListItem *listItemTwo = new DetailedListItem(listContent, "", "Schicht- und Pausendaten", captionsTwo, true);

    listItemOne->setValues(valuesOne);
    listItemTwo->setValues(valuesTwo);

    listContentLayout->addWidget(listItemOne);
    listContentLayout->addWidget(listItemTwo);*/
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


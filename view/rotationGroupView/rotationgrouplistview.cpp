#include "rotationgrouplistview.h"
#include "../view/flickcharm.h"
#include "../view/detailedlistitem.h"
#include "../view/iconconstants.h"
#include <QList>

const QList<QStringList> RotationGroupListView::rotationGroupCaptions = QList<QStringList>() << (QStringList() << tr("Workplace Count") <<tr("Total Duration"));

RotationGroupListView::RotationGroupListView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Rotation Groups"), parent),
    btnPlus(new QPushButton()),
    listContentLayout(new QVBoxLayout),
    scRotationGroups(new QScrollArea())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *listContent = new QWidget;

    btnPlus->setObjectName("plusIcon");
    btnPlus->setFixedSize(45, 45);
    connect(btnPlus, SIGNAL(clicked()), this, SLOT(btnPlusClicked()));

    scRotationGroups->setWidget(listContent);
    scRotationGroups->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scRotationGroups);

    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    mainLayout->addWidget(scRotationGroups);
    setLayout(mainLayout);

    addRotationGroup(0, "Rotationsgruppe 1", "3", "2h45");
}

// PUBLIC SLOTS
void RotationGroupListView::clear(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void RotationGroupListView::addRotationGroup(int id, const QString &name, const QString &wpCount, const QString &totalDuration){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << wpCount << totalDuration);
    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_ROTATION, name, rotationGroupCaptions, true, false, true);
    newListItem->setID(id);
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliRotationGroupClicked(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(remove(int)));
    listContentLayout->addWidget(newListItem);
}

// PUBLIC METHODS
QList<QAbstractButton*> * RotationGroupListView::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnPlus);
    return additions;
}

// PRIVATE SLOTS
void RotationGroupListView::btnPlusClicked(){
    emit create();
    emit showView(ViewType::ROTATION_GROUP_VIEW);
}

void RotationGroupListView::dliRotationGroupClicked(int id){
    emit selected(id);
    emit showView(ViewType::ROTATION_GROUP_VIEW);
}

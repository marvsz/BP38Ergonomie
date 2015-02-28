#include "workplacelistview.h"
#include "flickcharm.h"
#include <QVBoxLayout>
#include <QList>
#include <QStringList>

const QList<QStringList> WorkplaceListView::workplaceCaptions = QList<QStringList>() << (QStringList() << tr("Description") << tr("Code"));

WorkplaceListView::WorkplaceListView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Workplaces"), parent),
    btnPlus(new QPushButton(this)),
    listContentLayout(new QVBoxLayout),
    scWorkplaces(new QScrollArea())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *listContent = new QWidget;

    btnPlus->setObjectName("plusIcon");
    btnPlus->setFixedSize(45, 45);

    connect(btnPlus, SIGNAL(clicked()), this, SLOT(btnPlusClicked()));

    scWorkplaces->setWidget(listContent);
    scWorkplaces->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scWorkplaces);

    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

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
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", name, workplaceCaptions, true, false, true);
    newListItem->setValues(values);
    newListItem->setID(id);
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliWorkplaceClicked(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(remove(int)));
    listContentLayout->addWidget(newListItem);
}

//PUBLIC METHODS
QList<QAbstractButton*> * WorkplaceListView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnPlus);
    return additions;
}

//PRIVATE SLOTS
void WorkplaceListView::btnPlusClicked(){
    emit create();
    emit showView(ViewType::WORKPLACE_VIEW);
}

void WorkplaceListView::dliWorkplaceClicked(int id){
    emit selected(id);
    emit showView(ViewType::WORKPLACE_VIEW);
}

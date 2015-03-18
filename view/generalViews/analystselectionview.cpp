#include "analystselectionview.h"
#include "../separator.h"
#include "../flickcharm.h"

AnalystSelectionView::AnalystSelectionView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Analyst selection"), parent),
    btnCreateAnalyst(new QPushButton()),
    listContentLayout(new QVBoxLayout()),
    scAnalysts(new QScrollArea(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    btnCreateAnalyst->setFixedSize(45, 45);
    btnCreateAnalyst->setObjectName("plusIcon");

    connect(btnCreateAnalyst, SIGNAL(clicked()), this, SLOT(btnCreateAnalystClicked()));

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scAnalysts->setWidget(listContent);
    scAnalysts->setWidgetResizable(true);
    scAnalysts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scAnalysts);

    mainLayout->addWidget(scAnalysts);

    setLayout(mainLayout);

}
//PUBLIC METHODS
QList<QAbstractButton*> * AnalystSelectionView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnCreateAnalyst);
    return additions;
}

//PUBLIC SLOTS
void AnalystSelectionView::addAnalyst(QHash<QString, QVariant> values){
    QString name = QString("%1, %2").arg(values.value(DBConstants::COL_ANALYST_LASTNAME).toString()).arg(values.value(DBConstants::COL_ANALYST_FIRSTNAME).toString());

    DetailedListItem *newListItem = new DetailedListItem(this, "userIcon", name, QList<QStringList>(), true, false, true);

    newListItem->setID(values.value(DBConstants::COL_ANALYST_ID).toInt());
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliPressed(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteAnalyst(int)));
    listContentLayout->addWidget(newListItem);
}

void AnalystSelectionView::updateAnalyst(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_ANALYST_ID).toInt();
    int i = 0;
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QString name = QString("%1, %2").arg(values.value(DBConstants::COL_ANALYST_LASTNAME).toString()).arg(values.value(DBConstants::COL_ANALYST_FIRSTNAME).toString());
            dli->setName(name);
            break;
        }
        i++;
    }
}

void AnalystSelectionView::removeAnalyst(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            listContentLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void AnalystSelectionView::clearAnalysts(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//PRIVATE SLOTS
void AnalystSelectionView::dliPressed(int id){
    emit selectAnalyst(id);
    emit showView(ViewType::MAIN_MENU_VIEW);
}

void AnalystSelectionView::btnCreateAnalystClicked(){
    emit showPopUp(PopUpType::ANALYST_POPUP);
}

#include "analystselectionview.h"
#include "separator.h"
#include "iconconstants.h"
#include "flickcharm.h"

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

void AnalystSelectionView::add(int id, const QString &lastName, const QString &firstName){
    QString name = lastName + ", " + firstName;

    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_USER, name, QList<QStringList>(), true, false, true);

    newListItem->setID(id);
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliPressed(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(remove(int)));
    listContentLayout->addWidget(newListItem);
}

void AnalystSelectionView::clear(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//PRIVATE SLOTS
void AnalystSelectionView::dliPressed(int id){
    emit select(id);
    emit showView(ViewType::MAIN_MENU_VIEW);
}

void AnalystSelectionView::btnCreateAnalystClicked(){
    emit showPopUp(PopUpType::ANALYST_POPUP);
}

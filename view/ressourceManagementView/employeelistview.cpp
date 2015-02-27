#include "employeelistview.h"
#include "../view/iconconstants.h"
#include <QList>
#include "../view/flickcharm.h"

const QList<QStringList> EmployeeListView::employeeCaptions = QList<QStringList>() <<(QStringList() << tr("Description"));

EmployeeListView::EmployeeListView(QWidget *parent) :
       SimpleNavigateableWidget(tr("Employees"), parent),
       btnPlus(new QPushButton(this)),
       listContentLayout(new QVBoxLayout()),
       scEmployees(new QScrollArea())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *listContent = new QWidget;

    btnPlus->setObjectName("plusIcon");
    btnPlus->setFixedSize(45, 45);

    connect(btnPlus, SIGNAL(clicked()), this, SLOT(btnPlusClicked()));

    scEmployees->setWidget(listContent);
    scEmployees->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scEmployees);

    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    mainLayout->addWidget(scEmployees);

    this->setLayout(mainLayout);
}

void EmployeeListView::clear(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void EmployeeListView::addEmployee(int id, const QString &name, const QString &description, const QString &personalID){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << description << personalID);
    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_USER, name, employeeCaptions, true, false, true);
    newListItem->setValues(values);
    newListItem->setID(id);
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliEmployeeClicked(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(remove(int)));
    listContentLayout->addWidget(newListItem);
}

//PUBLIC METHODS
QList<QAbstractButton*> * EmployeeListView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnPlus);
    return additions;
}

//PRIVATE SLOTS
void EmployeeListView::btnPlusClicked(){
    emit create();
    emit showView(ViewType::EMPLOYEE_VIEW);
}

void EmployeeListView::dliEmployeeClicked(int id){
    emit selected(id);
    emit showView(ViewType::EMPLOYEE_VIEW);
}

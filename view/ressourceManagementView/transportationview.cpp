#include <QGridLayout>
#include "transportationview.h"
#include "../../enum.h"
#include "../flickcharm.h"
#include "../separator.h"
#include "../detailedlistitem.h"
#include "../../databaseHandler/dbconstants.h"

const QVector<QVariant> TransportationView::YES_NO_VALUE = QVector<QVariant>()<<true<<false;

TransportationView::TransportationView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Transportations"), parent),
    scTransportation(new QScrollArea),
    lblAddTransportation(new QLabel(tr("Add Transportation"))),
    lblName(new QLabel(tr("Name:"))),
    lblWeight(new QLabel(tr("Empty weight [kg]:"))),
    lblMaxLoad(new QLabel(tr("Max. load [kg]:"))),
    lblFixedRoller(new QLabel(tr("Fixed rollers:"))),
    lblBrakes(new QLabel(tr("Brakes:"))),
    txtBxName(new TextLineEdit()),
    numBxWeight(new NumberLineEdit()),
    numBxMaxLoad(new NumberLineEdit()),
    oscFixedRoller(new OptionSelectionControl()),
    oscBrakes(new OptionSelectionControl()),
    btnAdd(new QPushButton()),
    transportationListLayout(new QVBoxLayout())
{
    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddTransportation->setObjectName("lblHeader");
    txtBxName->setPlaceholderText(tr("name of the transportation"));
    numBxWeight->setPlaceholderText(tr("empty weight of the transportation"));
    numBxMaxLoad->setPlaceholderText(tr("maximum load weight of the transportation"));
    oscFixedRoller->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscBrakes->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scTransportation->setWidget(listContent);
    scTransportation->setWidgetResizable(true);
    listContent->setLayout(transportationListLayout);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scTransportation);

    QGridLayout *transportationDataLayout = new QGridLayout;
    transportationDataLayout->addWidget(lblAddTransportation, 0, 0, 1, 2, 0);
    transportationDataLayout->addWidget(lblName, 1, 0, 1, 1, 0);
    transportationDataLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    transportationDataLayout->addWidget(lblWeight, 2, 0, 1, 1, 0);
    transportationDataLayout->addWidget(numBxWeight, 2, 1, 1, 1, 0);
    transportationDataLayout->addWidget(lblMaxLoad, 3, 0, 1, 1, 0);
    transportationDataLayout->addWidget(numBxMaxLoad, 3, 1, 1, 1, 0);
    transportationDataLayout->addWidget(lblFixedRoller, 4, 0, 1, 1, 0);
    transportationDataLayout->addWidget(oscFixedRoller, 4, 1, 1, 1, 0);
    transportationDataLayout->addWidget(lblBrakes, 5, 0, 1, 1, 0);
    transportationDataLayout->addWidget(oscBrakes, 5, 1, 1, 1, 0);
    transportationDataLayout->addWidget(btnAdd, 6, 0, 1, 2, Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(transportationDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scTransportation);

    transportationListLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
}

TransportationView::~TransportationView(){}

// PUBLIC SLOTS

void TransportationView::addTransportation(QHash<QString, QVariant> values){
    QString fixedRollers = values.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool() ? tr("Yes") : tr("No");
    QString brakes = values.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool() ? tr("Yes") : tr("No");
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toString() << values.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toString()) << (QStringList() << fixedRollers << brakes);
    DetailedListItem *newListItem = new DetailedListItem(this, "transportationIcon", values.value(DBConstants::COL_TRANSPORTATION_NAME).toString(), transportationItemScheme, true, false, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_TRANSPORTATION_ID).toInt());
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteTransportation(int)));
    transportationListLayout->addWidget(newListItem);
}

void TransportationView::removeTransportation(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = transportationListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            transportationListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void TransportationView::updateTransportation(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_TRANSPORTATION_ID).toInt();
    int i = 0;
    while((item = transportationListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QString fixedRollers = values.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool() ? tr("Yes") : tr("No");
            QString brakes = values.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool() ? tr("Yes") : tr("No");
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toString() << values.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toString()) << (QStringList() << fixedRollers << brakes);
            dli->setName(values.value(DBConstants::COL_TRANSPORTATION_NAME).toString());
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void TransportationView::clearTransportations(){
    QLayoutItem *item;
    while((item = transportationListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}


// PRIVATE SLOTS
void TransportationView::btnAddClicked(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TRANSPORTATION_NAME, txtBxName->text());
    values.insert(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, numBxWeight->getValue());
    values.insert(DBConstants::COL_TRANSPORTATION_MAX_LOAD, numBxMaxLoad->getValue());
    values.insert(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, oscFixedRoller->getSelectedValue().toInt());
    values.insert(DBConstants::COL_TRANSPORTATION_BRAKES, oscBrakes->getSelectedValue().toInt());
    emit createTransportation(values);
    txtBxName->clear();
    numBxWeight->clear();
    numBxMaxLoad->clear();
    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);
}

#include "loadhandlingview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "../valuecontrol.h"
#include "../separator.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"
#include "../../databaseHandler/dbconstants.h"

/**
 * @brief Constructs a new Transportview
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
LoadHandlingView::LoadHandlingView(QWidget *parent) :
    TitledWidget(tr("Load handling"), parent),
    selectedTransportationID(0)
{

    main = new QWidget(this);
    control = new QWidget(this);

    QVBoxLayout *topGroupLayout = new QVBoxLayout;
    QHBoxLayout *menuLineLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    transportationListLayout = new QVBoxLayout;

    vlcGraspType = new ValueControl(TEXT,categoryScrollArea);
    vlcGraspType->setValues(false, graspValues,graspValues,QString(tr("GraspTypeIcons")));
    vlcGraspType->setText(tr("Grasptype:"));

    vlcHandlingType = new ValueControl(TEXT, categoryScrollArea);
    vlcHandlingType->setValues(true,HandlingTypeValues, HandlingTypeValues,QString());
    vlcHandlingType->setText(tr("loadhandling type:"));
    connect(vlcHandlingType, SIGNAL(valueChanged(QString)), this, SLOT(typeChanged(QString)));


    vlcWeight = new ValueControl(VALUE, categoryScrollArea);
    vlcWeight->setUnit(tr("kg"));
    vlcWeight->setValues(1, 100, weightValues, QString());
    vlcWeight->setText(tr("Last"));


    vlcDistance = new ValueControl(VALUE, categoryScrollArea);
    vlcDistance->setUnit(tr("m"));
    vlcDistance->setValues(0, 20, distanceValues, QString());
    vlcDistance->setText(tr("Weg"));

    lblTransportation = new QLabel(tr("Transportation:"));
    btnAddTransportation = new QPushButton();
    btnAddTransportation->setFixedSize(45, 45);
    btnAddTransportation->setObjectName("editIcon");

    QVector<QString>* options = new QVector<QString>();
    options->append(tr("Bockrollen"));
    options->append(tr("Bremsen"));

    QWidget *transportationList = new QWidget;
    transportationList->setLayout(transportationListLayout);

    topGroupLayout->addWidget(vlcGraspType);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(vlcHandlingType);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(vlcWeight);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(vlcDistance);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(lblTransportation);
    topGroupLayout->addWidget(transportationList);
    topGroupLayout->addWidget(btnAddTransportation);
    topGroupLayout->setAlignment(btnAddTransportation, Qt::AlignCenter);

    control->setLayout(topGroupLayout);

    categoryScrollArea->setWidget(control);
    categoryScrollArea->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);

    mainLayout->addLayout(menuLineLayout);
    mainLayout->addWidget(categoryScrollArea);


    this->setLayout(mainLayout);


    connect(btnAddTransportation, SIGNAL(clicked()), this, SLOT(btnAddTransportationClicked()));
}



LoadHandlingView::~LoadHandlingView()
{
}

// PUBLIC SLOTS
void LoadHandlingView::setLoadHandling(QHash<QString, QVariant> values){
    vlcGraspType->setValue(values.value(DBConstants::COL_TYPE_OF_GRASPING_NAME).toString());
    vlcHandlingType->setValue(values.value(DBConstants::COL_LOAD_HANDLING_TYPE_NAME).toString());
    vlcWeight->setValue(values.value(DBConstants::COL_LOAD_HANDLING_LOAD).toInt());
    vlcDistance->setValue(values.value(DBConstants::COL_LOAD_HANDLING_DISTANCE).toInt());
    selectedTransportationChanged(values.value(DBConstants::COL_LOAD_HANDLING_TRANSPORTATION_ID).toInt());
}

void LoadHandlingView::addTransportation(QHash<QString, QVariant> values){
    QString fixedRollers = values.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool() ? tr("Yes") : tr("No");
    QString brakes = values.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool() ? tr("Yes") : tr("No");
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toString() << values.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toString()) << (QStringList() << fixedRollers << brakes);
    DetailedListItem *newListItem = new DetailedListItem(this, "transportationIcon", values.value(DBConstants::COL_TRANSPORTATION_NAME).toString(), transportationItemScheme, false, true, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_TRANSPORTATION_ID).toInt());
    //connect(newListItem, SIGNAL(selected(int)), this, SLOT(dliTransportationSelected(int)));
    //connect(this, SIGNAL(exclusivTransporationSelection(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedTransportationChanged(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectTransportation(int)));
    connect(this, SIGNAL(selectedTransportation(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    transportationListLayout->addWidget(newListItem);
}

void LoadHandlingView::removeTransportation(int id){
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

void LoadHandlingView::updateTransportation(QHash<QString, QVariant> values){
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

void LoadHandlingView::clearTransportations(){
    QLayoutItem *item;
    while((item = transportationListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void LoadHandlingView::onLeaving(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TYPE_OF_GRASPING_NAME, vlcGraspType->getTextValue());
    values.insert(DBConstants::COL_LOAD_HANDLING_TYPE_NAME, vlcHandlingType->getTextValue());
    values.insert(DBConstants::COL_LOAD_HANDLING_LOAD, vlcWeight->getValue());
    values.insert(DBConstants::COL_LOAD_HANDLING_DISTANCE, vlcDistance->getValue());
    values.insert(DBConstants::COL_LOAD_HANDLING_TRANSPORTATION_ID, selectedTransportationID);
    emit saveLoadHandling(values);
}

// PRIVATE SLOTS
void LoadHandlingView::selectedTransportationChanged(int id){
    selectedTransportationID = id;
    emit selectedTransportation(id);
}

void LoadHandlingView::deselectTransportation(int id){
    if(id == selectedTransportationID)
        selectedTransportationID = 0;
}


void LoadHandlingView::typeChanged(QString newType){
    if(newType == tr("pulling and pushing"))
        vlcWeight->setValues(1, 2000, heavyWeightValues, QString());
    else
        vlcWeight->setValues(1, 100, weightValues, QString());
}

void LoadHandlingView::btnAddTransportationClicked(){
    emit showPopUp(PopUpType::TRANSPORTATION_POPUP);
}

#include "loadhandlingview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "../valuecontrol.h"
#include "../separator.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"

/**
 * @brief Constructs a new Transportview
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
LoadHandlingView::LoadHandlingView(QWidget *parent) :
    TitledWidget(tr("Load handling"), parent),
    selectedTransportation_ID(0)
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
    btnEditTransportation = new QPushButton();
    btnEditTransportation->setFixedSize(45, 45);
    btnEditTransportation->setObjectName("editIcon");

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
    topGroupLayout->addWidget(btnEditTransportation);
    topGroupLayout->setAlignment(btnEditTransportation, Qt::AlignCenter);

    control->setLayout(topGroupLayout);

    categoryScrollArea->setWidget(control);
    categoryScrollArea->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);

    mainLayout->addLayout(menuLineLayout);
    mainLayout->addWidget(categoryScrollArea);


    this->setLayout(mainLayout);


    connect(btnEditTransportation, SIGNAL(clicked()), this, SLOT(btnEditTransportationClicked()));
}



LoadHandlingView::~LoadHandlingView()
{
}

void LoadHandlingView::addTransportation(int id, const QString &name, int weight, int maxLoad, bool hasBrakes, bool hasFixedRoller){
    DetailedListItem *newListItem = new DetailedListItem(0, "transportationIcon", name, transportationItemScheme, false, true, false);
    newListItem->setID(id);
    QString brakes = hasBrakes ? tr("yes") : tr("no");
    QString fixedRoller = hasFixedRoller ? tr("yes") : tr("no");
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(weight) << QString::number(maxLoad)) << (QStringList()<<brakes<<fixedRoller);
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(dliTransportationSelected(int)));
    connect(this, SIGNAL(exclusivTransporationSelection(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    transportationListLayout->addWidget(newListItem);
}

void LoadHandlingView::clearTransportation(){
    QLayoutItem *item;
    while((item = transportationListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PRIVATE SLOTS
void LoadHandlingView::dliTransportationSelected(int id){
    emit exclusivTransporationSelection(id);
    selectedTransportation_ID = id;
}


void LoadHandlingView::typeChanged(QString newType){
    if(newType == tr("pulling and pushing"))
        vlcWeight->setValues(1, 2000, heavyWeightValues, QString());
    else
        vlcWeight->setValues(1, 100, weightValues, QString());
}

void LoadHandlingView::btnEditTransportationClicked(){
    emit showPopUp(PopUpType::TRANSPORTATION_POPUP);
}

// GETTER

QString LoadHandlingView::getHandlingType() const {
    return vlcHandlingType->getTextValue();
}

QString LoadHandlingView::getGraspType() const{
    return vlcGraspType->getTextValue();
}

int LoadHandlingView::getWeight() {
    return vlcWeight->getValue();
}

int LoadHandlingView::getDistance(){
    return vlcDistance->getValue();
}

int LoadHandlingView::getSelectedTransportation() const{
    return selectedTransportation_ID;
}

// SETTER

void LoadHandlingView::setHandlingType(const QString &handlingType){
    vlcHandlingType->setValue(handlingType);
}

void LoadHandlingView::setGraspType(const QString &graspType){
    vlcGraspType->setValue(graspType);
}

void LoadHandlingView::setWeight(int weight){
    vlcWeight->setValue(weight);
}

void LoadHandlingView::setDistance(int distance){
    vlcDistance->setValue(distance);
}

void LoadHandlingView::setSelectedTransportation(int id){
    dliTransportationSelected(id);
}

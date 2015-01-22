#include <QGridLayout>
#include "transportationview.h"
#include "../enum.h"
#include "flickcharm.h"
#include "separator.h"
#include "detailedlistitem.h"
#include "iconconstants.h"

const QVector<QVariant> TransportationView::YES_NO_VALUE = QVector<QVariant>()<<true<<false;

TransportationView::TransportationView(QWidget *parent) :
    QWidget(parent),
    scTransportation(new QScrollArea),
    lblAddTransportation(new QLabel(tr("Add Transportation"))),
    lblViewName(new QLabel(tr("Transportations"))),
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
    btnBack(new QPushButton()),
    btnAdd(new QPushButton()),
    transportationListLayout(new QVBoxLayout())
{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddTransportation->setObjectName("lblHeader");
    txtBxName->setPlaceholderText(tr("name of the transportation"));
    numBxWeight->setPlaceholderText(tr("empty weight of the transportation"));
    numBxMaxLoad->setPlaceholderText(tr("maximum load weight of the transportation"));
    oscFixedRoller->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscBrakes->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

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
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addLayout(transportationDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scTransportation);

    setLayout(mainLayout);
}

TransportationView::~TransportationView(){}

// PUBLIC

QString TransportationView::getName() const {
    return txtBxName->text();
}

int TransportationView::getWeight() const{
    return numBxWeight->getValue();
}

int TransportationView::getMaxLoad() const{
    return numBxMaxLoad->getValue();
}

bool TransportationView::hasFixedRoller() const{
    return oscFixedRoller->getSelectedValue().toBool();
}

bool TransportationView::hasBrakes() const{
    return oscBrakes->getSelectedValue().toBool();
}

// PUBLIC SLOTS
void TransportationView::addTransportation(int id, const QString &name, int weight, int maxLoad, bool fixedRollers, bool brakes){
    DetailedListItem *newListItem = new DetailedListItem(0, IconConstants::ICON_TRANSPORTATION, name, transportationItemScheme, true, false, false);
    newListItem->setID(id);
    QString strHasBrakes = brakes ? tr("yes") : tr("no");
    QString strHasFixedRoller = fixedRollers ? tr("yes") : tr("no");
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(weight) << QString::number(maxLoad)) << (QStringList() << strHasFixedRoller << strHasBrakes);
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteTransportation(int)));
    transportationListLayout->addWidget(newListItem);
}

void TransportationView::setWeight(int weight){
    numBxWeight->setValue(weight);
}

void TransportationView::setMaxLoad(int maxLoad){
    numBxMaxLoad->setValue(maxLoad);
}

void TransportationView::setFixedRoller(QVariant value){
    oscFixedRoller->setSelectedByValue(value.toInt());
}

void TransportationView::setBrakes(QVariant value){
    oscBrakes->setSelectedByValue(value.toInt());
}

void TransportationView::clear(){
    QLayoutItem *item;
    while((item = transportationListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PRIVATE SLOTS
void TransportationView::btnAddClicked(){
    emit saveTransportation();
    txtBxName->clear();
    numBxWeight->clear();
    numBxMaxLoad->clear();
    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);
}

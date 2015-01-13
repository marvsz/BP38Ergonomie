#include "workprocessmetadataview.h"
#include <QGridLayout>
#include "separator.h"
#include "detailedlistitem.h"

const QStringList WorkProcessMetaDataView::IMPULSE_INTENSITY_TEXTS = QStringList()<<tr("small")<<tr("middle")<<tr("strong");
const QVector<QVariant> WorkProcessMetaDataView::IMPULSE_INTENSITY_VALUES = QVector<QVariant>()<<1<<5<<10;

const QVector<QString> WorkProcessMetaDataView::MTM_CODE_TEXTS = QVector<QString>()<<tr("takeing/placing")<<tr("tool handling")<<tr("placing")<<tr("operate")<<tr("body movement");
const QVector<QString> WorkProcessMetaDataView::MTM_CODE_VALUES = QVector<QString>()<<"A"<<"H"<<"P"<<"B"<<"K";

const QList<QStringList> WorkProcessMetaDataView::equipmentItemScheme = QList<QStringList>() << (QStringList() << tr("recoil count") << tr ("recoil intensity")) << (QStringList() << tr("vibration count") << tr("vibration intensity"));

WorkProcessMetaDataView::WorkProcessMetaDataView(QWidget *parent) : QWidget(parent),
    lblDescription(new QLabel(tr("Description:"))),
    lblWorkingHeight(new QLabel(tr("Working height [cm]:"))),
    lblDistance(new QLabel(tr("Distance [cm]:"))),
    lblImpulseIntensity(new QLabel(tr("Impulse intensity:"))),
    lblImpulseCount(new QLabel(tr("Impulse count:"))),
    lblEquipment(new QLabel(tr("Equipment:"))),
    txtBxDescription(new TextLineEdit()),
    vcMTMCode(new ValueControl(TEXT)),
    numBxWorkingHeight(new NumberLineEdit()),
    numBxDistance(new NumberLineEdit()),
    oscImpulseIntensity(new OptionSelectionControl()),
    numBxImpulseCount(new NumberLineEdit()),
    equipmentListLayout(new QVBoxLayout)
{
    txtBxDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    txtBxDescription->setPlaceholderText(tr("Description of the working process"));
    numBxWorkingHeight->setPlaceholderText(tr("Working height of the process [cm]"));
    numBxDistance->setPlaceholderText(tr("Distance from produced product [cm]"));
    numBxImpulseCount->setPlaceholderText(tr("Count of impulses"));

    oscImpulseIntensity->setValues(IMPULSE_INTENSITY_TEXTS, IMPULSE_INTENSITY_VALUES);

    vcMTMCode->setText(tr("MTM Code:"));
    vcMTMCode->setTextHint(tr("MTM Code of the process"));
    vcMTMCode->setValues(true, MTM_CODE_TEXTS, MTM_CODE_VALUES, QString(""));

    QWidget *equipmentList = new QWidget;
    equipmentList->setLayout(equipmentListLayout);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lblDescription, 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxDescription, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3), 1, 0, 1, 2, 0);
    mainLayout->addWidget(vcMTMCode, 2, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3), 3, 0, 1, 2, 0);
    mainLayout->addWidget(lblWorkingHeight, 4, 0, 1, 1, 0);
    mainLayout->addWidget(numBxWorkingHeight, 4, 1, 1, 1, 0);
    mainLayout->addWidget(lblDistance, 5, 0, 1, 1, 0);
    mainLayout->addWidget(numBxDistance, 5, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 6, 0, 1, 2, 0);
    mainLayout->addWidget(lblImpulseIntensity, 7, 0, 1, 1, 0);
    mainLayout->addWidget(oscImpulseIntensity, 7, 1, 1, 1, 0);
    mainLayout->addWidget(lblImpulseCount, 8, 0, 1, 1, 0);
    mainLayout->addWidget(numBxImpulseCount, 8, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3), 9, 0, 1, 2, 0);
    mainLayout->addWidget(lblEquipment, 10, 0, 1, 1, 0);
    mainLayout->addWidget(equipmentList, 11, 0, 1, 3, 0);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 9, 0, 1, 2, 0);

    setLayout(mainLayout);
}

WorkProcessMetaDataView::~WorkProcessMetaDataView()
{

}
//PUBLIC SLOTS
void WorkProcessMetaDataView::setWorkProcessMetaData(const QString &desc, const QString &mtmCode, int workingHeight, int distance, int impulseIntensity, int impulseCount){
    txtBxDescription->setText(desc);
    vcMTMCode->setValue(mtmCode);
    numBxWorkingHeight->setValue(workingHeight);
    numBxDistance->setValue(distance);
    oscImpulseIntensity->setSelectedValue(impulseIntensity);
    numBxImpulseCount->setValue(impulseCount);
}

void WorkProcessMetaDataView::addEquipment(int id, const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity){
    DetailedListItem *newListItem = new DetailedListItem(0, "", name, equipmentItemScheme, false, true, false);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(recoilCount) << QString::number(recoilIntensity)) << (QStringList() << QString::number(vibrationCount) << QString::number(vibrationIntensity));
    newListItem->setValues(values);
    equipmentListLayout->addWidget(newListItem);
}

void WorkProcessMetaDataView::clearEquipment(){
    QLayoutItem *item;
    while((item = equipmentListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}


//GETTER
QString WorkProcessMetaDataView::getDescription() const{
    return txtBxDescription->text();
}
QString WorkProcessMetaDataView::getMTMCode() const{
    return vcMTMCode->getTextValue();
}
int WorkProcessMetaDataView::getWorkingHeight() const{
    return numBxWorkingHeight->getValue();
}
int WorkProcessMetaDataView::getDistance() const{
    return numBxDistance->getValue();
}
int WorkProcessMetaDataView::getImpulseIntensity() const{
    return oscImpulseIntensity->getSelectedValue().toInt();
}
int WorkProcessMetaDataView::getImpulseCount() const{
    return numBxImpulseCount->getValue();
}


#ifndef WORKPROCESSMETADATAVIEW_H
#define WORKPROCESSMETADATAVIEW_H

#include "../navigation/titledwidget.h"
#include <QLabel>
#include <QPushButton>
#include "../numberlineedit.h"
#include "../valuecontrol.h"
#include "../optionselectioncontrol.h"
#include "../interfaces/iequipmentlist.h"
#include "../../databaseHandler/dbconstants.h"

class WorkProcessMetaDataView : public TitledWidget, IEquipmentList
{
    Q_OBJECT
    Q_INTERFACES(IEquipmentList)
public:
    explicit WorkProcessMetaDataView(QWidget *parent = 0);
    ~WorkProcessMetaDataView();

    QString getDescription() const;
    QString getMTMCode() const;
    int getWorkingHeight() const;
    int getDistance() const;
    int getImpulseIntensity() const;
    int getImpulseCount() const;

signals:
    void selectEquipmentExclusive(int id);

    void createEquipment(QHash<QString, QVariant> values);
    void deleteEquipment(int id);
    void selectEquipment(int id);

public slots:
    void setWorkProcessMetaData(const QString &desc, const QString &mtmCode, int workingHeight, int distance, int impulseIntensity, int impulseCount);

    void addEquipment(QHash<QString, QVariant> values);
    void updateEquipment(QHash<QString, QVariant> values);
    void removeEquipment(int id);
    void clearEquipments();

private slots:
    void dliEquipmentSelected(int id);
    void dliEquipmentDeselect(int id);
    void btnCreateEquipmentClicked();

private:
    QLabel *lblDescription;
    QLabel *lblWorkingHeight;
    QLabel *lblDistance;
    QLabel *lblImpulseIntensity;
    QLabel *lblImpulseCount;
    QLabel *lblEquipment;

    QPushButton *btnCreateEquipment;

    TextLineEdit *txtBxDescription;
    ValueControl *vcMTMCode;
    NumberLineEdit *numBxWorkingHeight;
    NumberLineEdit *numBxDistance;
    OptionSelectionControl *oscImpulseIntensity;
    NumberLineEdit *numBxImpulseCount;

    const QVector<QString> MTM_CODE_TEXTS = QVector<QString>()<<tr("taking/placing")<<tr("tool handling")<<tr("placing")<<tr("operate")<<tr("body movement");
    const QVector<QString> MTM_CODE_VALUES  = QVector<QString>()<<"A"<<"H"<<"P"<<"B"<<"K";
    const QStringList IMPULSE_INTENSITY_TEXTS = QStringList()<<tr("small")<<tr("middle")<<tr("strong");
    const QVector<QVariant> IMPULSE_INTENSITY_VALUES = QVector<QVariant>()<<1<<5<<10;
    const QList<QStringList> equipmentItemScheme = QList<QStringList>() << (QStringList() << tr("recoil count") << tr ("recoil intensity")) << (QStringList() << tr("vibration count") << tr("vibration intensity"));

    QVBoxLayout *equipmentListLayout;

    int selectedEquipment_ID;
};

#endif // WORKPROCESSMETADATAVIEW_H

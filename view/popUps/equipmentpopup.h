#ifndef EQUIPMENTPOPUP_H
#define EQUIPMENTPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../interfaces/iequipment.h"
#include "../numberlineedit.h"
#include "../../databaseHandler/dbconstants.h"

class EquipmentPopUp : public AbstractPopUpWidget, IEquipment
{
    Q_OBJECT
    Q_INTERFACES(IEquipment)
public:
    explicit EquipmentPopUp(QWidget *parent = 0);
    ~EquipmentPopUp();

signals:
    void saveEquipment(QHash<QString, QVariant> values);

public slots:
    void setEquipment(QHash<QString, QVariant>){}

private slots:
    void onConfirm();
    void onClose();

private:
    TextLineEdit *txtBxName;
    NumberLineEdit *numBxRecoilCount;
    NumberLineEdit *numBxRecoilIntensity;
    NumberLineEdit *numBxVibrationCount;
    NumberLineEdit *numBxVibrationIntensity;

};

#endif // EQUIPMENTPOPUP_H

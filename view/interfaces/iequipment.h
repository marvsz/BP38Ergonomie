#ifndef IEQUIPMENT
#define IEQUIPMENT

#include <QtPlugin>

class IEquipment{

signals:
    virtual void saveEquipment(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setEquipment(QHash<QString, QVariant> values) = 0;

};

#define IEquipment_iid "IEquipment"
Q_DECLARE_INTERFACE(IEquipment, IEquipment_iid)

#endif // IEQUIPMENT

